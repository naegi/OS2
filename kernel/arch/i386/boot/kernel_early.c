#include <libk/utils.h>

#include <kernel/i386/asm/io.h>
#include <kernel/i386/gdt.h>
#include <kernel/i386/interrupts.h>
#include <kernel/i386/kcall.h>
#include <kernel/i386/multiboot.h>
#include <kernel/i386/paging.h>
#include <kernel/i386/serial.h>
#include <kernel/i386/vga/text.h>
#include <kernel/i386/vga/console.h>

#include <kernel/i386/regs.h>

#include <libk/io.h>
#include <libk/utils.h>

void bpoint(regs_t regs);
void bpoint(regs_t reg){
    // Funky function for test prupose
    printfk("%x -- %x", reg.eflags, reg.eip);
    for(;;);
}

void kernel_early(multiboot_info_t*, uint32_t);

void kernel_early(multiboot_info_t* mbd, uint32_t magic){
    UNUSED(mbd);
    UNUSED(magic);



    gdt_init();
    interrupts_init();
    paging_init();

    kcall_init();
    kcall(0x10, (void*)kcall_init);

    vga_text_init();
    vga_console_init();
    serial_init();

    printfk("%c\n%s\ntest\n%d \n%x\n%o\n", 'a', "Un string", 51, 0xCE, 0xCE);
}
