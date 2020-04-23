#include <kernel/i386/interrupts.h>
#include <kernel/i386/kcall.h>


void kcall_init(){
    interrupts_install(0x80, (void*) kcall_handler_asm, true);

}

void kcall_handler_(regs_t regs){
    uint32_t kcall_no = regs.eax;
    void* data = (void*) regs.ebx;
    UNUSED(data);
    UNUSED(kcall_no);
}
