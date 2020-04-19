#include <libk/utils.h>

#include <kernel/i386/multiboot.h>
#include <kernel/i386/vga_text.h>
#include <kernel/i386/serial.h>
#include <kernel/i386/asm/io.h>
#include <libk/utils.h>

void kernel_early(multiboot_info_t*, uint32_t);

void kernel_early(multiboot_info_t* mbd, uint32_t magic){
    UNUSED(mbd);
    UNUSED(magic);

    vga_text_init();
    serial_init();
}
