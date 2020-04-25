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
    UNUSED(magic);



    gdt_init();
    interrupts_init();
    paging_init();

    kcall_init();
    kcall(0x10, (void*)kcall_init);

    vga_text_init();
    vga_console_init();
    serial_init();

    log_set_level(LOG_DEBUG);
    debug("Meuh");
    info("TEst");
    warn("BAH");
    err("BOUH %d", 4 + 4);
    printfk("TEST\n");
    kassert_m(0==1, "BOUH");

}
