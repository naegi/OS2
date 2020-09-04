#include <kernel/i386/regs.h>
#include <kernel/i386/kcall.h>
#include <kernel/process.h>
#include <kernel/i386/memory_management.h>
#include <kernel/i386/paging.h>
#include <libk/string.h>
#include <libk/kassert.h>


static process_t* current_process = NULL;

static process_t processes[3];

static int i = 0;


void process_init(){

}

static void grab_no_return(){
    kcall(KCALL_HALT, NULL);

}

void process_create(void* entry_point){
    process_t *process = &processes[i];
    i++;

    if(current_process != NULL){
        process->next = current_process->next;
        current_process->next = process;
    }
    else{
        current_process = process;
        process->next = process;
    }

    // TODO: ask for a PAGE and not a BLOCK or rename get block
    // get a page directory and identity map it
    process->cr3 = (uint32_t)memory_management_get_block();
    kassert(process->cr3 != BLOCK_ERROR);

    paging_map_4MB_kernel(process->cr3, process->cr3);
    memset((void*)process->cr3, 0, BLOCK_SIZE);

    // Allow kernel reading
    // TODO: When init will be out of kernel, we should set paging flag to PAGING_SUPERVISOR
    paging_map_kernel((uint32_t*)process->cr3, PAGING_USER | PAGING_READONLY | PAGING_PRESENT);


    // get a stack.
    uint32_t useresp_low = (uint32_t) memory_management_get_block();
    kassert(useresp_low != BLOCK_ERROR);

    // identity map it for the process and for the kernel
    paging_map_4MB_kernel(useresp_low, useresp_low);
    paging_map_4MB((uint32_t*)process->cr3, useresp_low, useresp_low, PAGING_USER | PAGING_RW | PAGING_PRESENT);

    // The stack grows downwards
    process->regs.useresp = useresp_low + (BLOCK_SIZE) ; //- sizeof(uint32_t);

    // if function returns, should not go anywhere => redirect to grab_noreturn
    process->regs.useresp -= sizeof(uint32_t);
    *(uint32_t*)process->regs.useresp = (uint32_t)grab_no_return;


    process->regs.ss = process->regs.ds
        = process->regs.fs
        = process->regs.es
        = process->regs.gs
        = 0x23;
    process->regs.cs = 0x1B;

    process->regs.eip = (uint32_t)entry_point;

}

void process_start(){
    process_jump((void*)current_process->regs.eip,
                 (void*)current_process->cr3,
                 (void*)current_process->regs.useresp);
    for(;;);
}

void process_yield_current(regs_t* regs){
    memcpy(&current_process->regs, regs, sizeof *regs);
    current_process = current_process->next;
    memcpy(regs, &current_process->regs, sizeof *regs);
}

