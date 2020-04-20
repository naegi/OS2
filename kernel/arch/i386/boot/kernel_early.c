#include <libk/utils.h>

#include <kernel/i386/asm/io.h>
#include <kernel/i386/gdt.h>
#include <kernel/i386/multiboot.h>
#include <kernel/i386/serial.h>
#include <kernel/i386/vga/text.h>
#include <kernel/i386/vga/console.h>

#include <libk/io.h>
#include <libk/utils.h>

void kernel_early(multiboot_info_t*, uint32_t);

void kernel_early(multiboot_info_t* mbd, uint32_t magic){
    UNUSED(mbd);
    UNUSED(magic);


    gdt_init();
    vga_text_init();
    vga_console_init();
    serial_init();

    printfk("%c\n%s\ntest\n%d \n%x\n%o\n", 'a', "Un string", 51, 0xCE, 0xCE);
}
