#include <libk/logging.h>
#include <kernel/i386/interrupts.h>
#include <kernel/i386/kcall.h>

#include <kernel/i386/memory_management.h>
#include <kernel/i386/vga/console.h>
#include <kernel/i386/serial.h>

void kcall_init(){
    interrupts_install(0x80, (void*) kcall_handler_asm, true);
}

static void kcall_write(kcall_write_t* write_data){

    //TODO: test memory access is allowed by user;

    if(write_data->fd == 1){ // stdout
        serial_write(write_data->buf, write_data->count);
        vga_console_write(write_data->buf, write_data->count);
    }
}

static void kcall_mmap(kcall_mmap_t* mmap_data){
    if(mmap_data->length > (1<<12))
        err_func("mmap for length > 4KB is not yet supported");
    mmap_data->addr = memory_management_get_block();
}

static void kcall_unmmap(kcall_unmmap_t* unmmap_data){
    if(unmmap_data->length > (1<<12))
        err_func("unmmap for length > 4KB is not yet supported");
    memory_management_free_block(unmmap_data->addr);
}


void kcall_handler_(regs_t regs){
    uint32_t kcall_no = regs.eax;
    void* data = (void*) regs.ebx;
    UNUSED(data);

    switch (kcall_no){
        case KCALL_WRITE: // FIRST ! Because logging uses kcall for now! Even in kernel!
            kcall_write((kcall_write_t*)data);
            break;
        case KCALL_MMAP:
            kcall_mmap((kcall_mmap_t*)data);
            break;
        case KCALL_UNMMAP:
            kcall_unmmap((kcall_unmmap_t*)data);
            break;
        default:
            err("Unsupported kcall no %d", kcall_no);
    }
}
