#include <libk/utils.h>
#include <kernel/i386/vga_text.h>

static uint16_t* const vga_text_base_address = (uint16_t*) 0xB8000;

static struct {
    uint8_t x;
    uint8_t y;
    uint8_t foreground_colour;
    uint8_t background_colour;
} vga_text_cursor;

void vga_text_init(){
    vga_text_cursor.x = vga_text_cursor.y = 0;
    vga_text_cursor.background_colour = VGA_TEXT_COLOR_BLACK; // Black
    vga_text_cursor.foreground_colour = VGA_TEXT_COLOR_WHITE;
    vga_text_clean();
}

void vga_text_putchar(char c){
    uint16_t* const loc = vga_text_base_address + (vga_text_cursor.y * 80 + vga_text_cursor.x);

    switch (c) {
        case '\n':
            vga_text_cursor.x = 0;
            vga_text_cursor.y++;
            break;
        default:
            *loc = (uint16_t) c | (uint16_t)(vga_text_cursor.foreground_colour << 8)
                                | (uint16_t)(vga_text_cursor.background_colour << 12);
            vga_text_cursor.x++;
    }


    if(vga_text_cursor.x == 80){
        vga_text_cursor.x = 0;
        vga_text_cursor.y++;
    }
    if(vga_text_cursor.y == 25){
        // TODO: scroll
        vga_text_cursor.y = 24;
    }
}

void vga_text_clean(){
    // TODO: use memset
    for (uint8_t x = 0; x < 80; ++x) {
        for (uint8_t y = 0; y < 25; ++y) {
            uint16_t* const loc = vga_text_base_address + (y * 80 + x);
            *loc = 0;
        }
    }
}


void vga_text_set_mode(uint8_t foreground_colour, uint8_t background_colour){
    vga_text_cursor.background_colour = background_colour & 0xF;
    vga_text_cursor.foreground_colour = foreground_colour & 0xF;
}

void vga_text_write(const char* c, size_t size){
    for (size_t i = 0; i < size; ++i) {
        vga_text_putchar(c[i]);
    }
}
