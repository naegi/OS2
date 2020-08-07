#include <libk/utils.h>

#include <kernel/i386/vga/console.h>
#include <kernel/i386/vga/text.h>

#define CONSOLE_MODE_TEXT           0x0
#define CONSOLE_MODE_CONTROL_EARLY  0x1
#define CONSOLE_MODE_CONTROL        0x2


#define CONTROL_BUFFER_SIZE 15

typedef struct {
    vga_text_control_t text;
    int mode;

    // Store control data
    // This is a non-zero terminated string length is in buf_used
    char control_buffer[CONTROL_BUFFER_SIZE];
    int buf_used;
} vga_console_control_t;

void vga_console_init(){
    vga_console_reset();
}

static vga_console_control_t ctrl = {0};

static void vga_console_reset_attributes(){
    ctrl.text.color.foreground = VGA_TEXT_COLOR_LIGHT_GRAY;
    ctrl.text.color.background = VGA_TEXT_COLOR_BLACK;
}

void vga_console_reset(){
    ctrl.text.cursor.x = ctrl.text.cursor.y = 0;
    vga_console_reset_attributes();
    vga_text_clear();
}

void vga_console_write(const void* buf, size_t nbyte){
    for (size_t i = 0; i < nbyte; ++i) {
        vga_console_putchar(*((char*)buf + i));
    }
}

void vga_console_puts(const char *s){
    while(*s != 0){
        vga_console_putchar(*s);
        s++;
    }
}

static void vga_console_set_display_attribute(){
    // Attributes are of form {attr1};{attr2}m
    char buff[CONTROL_BUFFER_SIZE+1];

    char* loc = ctrl.control_buffer;
    char* end = ctrl.control_buffer + ctrl.buf_used;

    while(loc <= end){
        char* buff_loc = buff;
        while(loc < end && *loc != ';'){
            *buff_loc = *loc;
            buff_loc++;
            loc++;
        }
        loc++; // ignore ';'
        *buff_loc = 0;

        int att = atoi(buff);

        if(att == 0)
            vga_console_reset_attributes();
        if(att / 10 == 3){ // set foreground color
            switch (att % 10) {
                case 0:
                    ctrl.text.color.foreground = VGA_TEXT_COLOR_BLACK;
                    break;
                case 1:
                    ctrl.text.color.foreground = VGA_TEXT_COLOR_RED;
                    break;
                case 2:
                    ctrl.text.color.foreground = VGA_TEXT_COLOR_GREEN;
                    break;
                case 3:
                    ctrl.text.color.foreground = VGA_TEXT_COLOR_YELLOW;
                    break;
                case 4:
                    ctrl.text.color.foreground = VGA_TEXT_COLOR_BLUE;
                    break;
                case 5:
                    ctrl.text.color.foreground = VGA_TEXT_COLOR_MAGENTA;
                    break;
                case 6:
                    ctrl.text.color.foreground = VGA_TEXT_COLOR_CYAN;
                    break;
                case 7:
                    ctrl.text.color.foreground = VGA_TEXT_COLOR_WHITE;
                    break;
            }

        }
        if(att / 10 == 4){ // set background color
            switch (att % 10) {
                case 0:
                    ctrl.text.color.background = VGA_TEXT_COLOR_BLACK;
                    break;
                case 1:
                    ctrl.text.color.background = VGA_TEXT_COLOR_RED;
                    break;
                case 2:
                    ctrl.text.color.background = VGA_TEXT_COLOR_GREEN;
                    break;
                case 3:
                    ctrl.text.color.background = VGA_TEXT_COLOR_YELLOW;
                    break;
                case 4:
                    ctrl.text.color.background = VGA_TEXT_COLOR_BLUE;
                    break;
                case 5:
                    ctrl.text.color.background = VGA_TEXT_COLOR_MAGENTA;
                    break;
                case 6:
                    ctrl.text.color.background = VGA_TEXT_COLOR_CYAN;
                    break;
                case 7:
                    ctrl.text.color.background = VGA_TEXT_COLOR_WHITE;
                    break;
            }

        }
    }

}

static void vga_console_scroll_if_needed(){
    if(ctrl.text.cursor.x == VGA_SCREEN_WIDTH){
        ctrl.text.cursor.x = 0;
        ctrl.text.cursor.y++;
    }
    if(ctrl.text.cursor.y == VGA_SCREEN_HEIGHT){
        ctrl.text.cursor.y--;
        vga_text_scroll(1);
    }
}


void vga_console_putchar(char c){
    // TODO: Make it more VT100 compliant: cf http://www.termsys.demon.co.uk/vtansi.htm for escape codes

    switch (ctrl.mode) {
        case CONSOLE_MODE_CONTROL:
            switch (c) {
                case 'm':
                    vga_console_set_display_attribute();
                    ctrl.mode = CONSOLE_MODE_TEXT;
                    break;
                default:
                    if(ctrl.buf_used == CONTROL_BUFFER_SIZE){
                        ctrl.mode = CONSOLE_MODE_TEXT; // Order IS important !
                        vga_console_puts("Buffer overflowed\n");
                    }
                    else {
                        ctrl.control_buffer[ctrl.buf_used] = c;
                        ctrl.buf_used++;
                    }
            }
            break; //!

        case CONSOLE_MODE_CONTROL_EARLY:
            switch (c) {
                case '[':
                    ctrl.mode = CONSOLE_MODE_CONTROL;
                    ctrl.buf_used=0;
                    return;
                case 'c': // Reset terminal
                    vga_console_reset();
                    return;
                default: // Failed to go into control mode
                    ctrl.mode = CONSOLE_MODE_TEXT;
            }
            //nobreak !

        case CONSOLE_MODE_TEXT:
            switch (c) {
                case '\n':
                    ctrl.text.cursor.x = 0;
                    ctrl.text.cursor.y++;
                    break;
                case 0x1B: // Escape
                    ctrl.mode = CONSOLE_MODE_CONTROL_EARLY; // wait for '[' or for other codes
                    break;
                default:
                    vga_text_write(&ctrl.text, c);
                    ctrl.text.cursor.x++;
            }
    }


    vga_console_scroll_if_needed();

}
