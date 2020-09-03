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

#include <kernel/i386/memory_management.h>

#include <kernel/i386/regs.h>

#include <libk/io.h>
#include <libk/logging.h>
#include <libk/kassert.h>
#include <libk/utils.h>

void bpoint(regs_t regs, uint32_t code);
void bpoint(regs_t reg, uint32_t code){
    // Funky function for test prupose
    UNUSED(code);
    info("Exception. Received code %d from eip %x", reg.err_co, reg.eip);
    for(;;);
}

void kernel_early(multiboot_info_t*, uint32_t);

void kernel_early(multiboot_info_t* mbd, uint32_t magic){
    UNUSED(mbd);
    gdt_init();
    interrupts_init();
    kcall_init();

    vga_text_init();
    vga_console_init();
    serial_init();

    log_set_level(LOG_DEBUG);
    info("Welcome");

    kassert_m(magic == 0x2BADB002, "Wrong multiboot magic! Everything is fucked up. Bye")

    memory_management_init(mbd);

    paging_init();
}
