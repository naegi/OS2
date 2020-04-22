#include <libk/utils.h>

#include <kernel/i386/vga/console.h>
#include <kernel/i386/vga/text.h>


static vga_text_control_t ctrl;

void vga_console_init(){
    vga_console_reset();
}

void vga_console_reset(){
    ctrl.cursor.x = ctrl.cursor.y = 0;
    ctrl.color.foreground = VGA_TEXT_COLOR_LIGHT_GRAY;
    ctrl.color.background = VGA_TEXT_COLOR_BLACK;
    vga_text_clear();
}

void vga_console_write(const void* buf, size_t nbyte){
    for (size_t i = 0; i < nbyte; ++i) {
        vga_text_write(&ctrl, *((char*)buf + i));
    }
}

void vga_console_puts(const char *s){
    while(*s != 0){
        vga_console_putchar(*s);
        s++;
    }
}

void vga_console_putchar(char c){
    // TODO: Make it more VT100 compliant: cf http://www.termsys.demon.co.uk/vtansi.htm for escape codes
    switch (c) {
        case '\n':
            ctrl.cursor.x = 0;
            ctrl.cursor.y++;
            break;
        default:
            vga_text_write(&ctrl, c);
            ctrl.cursor.x++;
    }

    if(ctrl.cursor.x == VGA_SCREEN_WIDTH){
        ctrl.cursor.x = 0;
        ctrl.cursor.y++;
    }
    if(ctrl.cursor.y == VGA_SCREEN_HEIGHT){
        ctrl.cursor.y--;
        vga_text_scroll(1);
    }

}
