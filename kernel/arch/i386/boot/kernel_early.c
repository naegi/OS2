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

void bpoint(regs_t regs);
void bpoint(regs_t reg){
    // Funky function for test prupose
    info("%x -- %x", reg.eflags, reg.eip);
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
    kcall_mmap_t mmap_data = {0};
    kcall(KCALL_MMAP, &mmap_data);
    info("Got memory at 0x%X", mmap_data.addr);
    kcall(KCALL_MMAP, &mmap_data);
    info("Got memory at 0x%X", mmap_data.addr);

    info("Freeing memory at 0x%X", mmap_data.addr);
    kcall(KCALL_UNMMAP, &(kcall_unmmap_t){.addr=mmap_data.addr});

    kcall(KCALL_MMAP, &mmap_data);
    info("Got memory at 0x%X", mmap_data.addr);

    paging_init();

}
