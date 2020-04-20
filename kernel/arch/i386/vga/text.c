#include <libk/utils.h>
#include <kernel/i386/vga/text.h>

static uint16_t* const vga_text_base_address = (uint16_t*) 0xB8000;

void vga_text_init(){
}

void vga_text_clear(){
    // TODO: use memset
    for (uint8_t x = 0; x < VGA_SCREEN_WIDTH ; ++x) {
        for (uint8_t y = 0; y < VGA_SCREEN_HEIGHT; ++y) {
            uint16_t* const loc = vga_text_base_address + (y*VGA_SCREEN_WIDTH + x);
            *loc = 0;
        }
    }
}

void vga_text_scroll(uint8_t n){
    if(n >= VGA_SCREEN_HEIGHT){
        vga_text_clear();
        return;
    }

    size_t diff = VGA_SCREEN_WIDTH * n;


    for (size_t y = 0; y < VGA_SCREEN_HEIGHT - n; ++y) {
        //TODO: use memmove()
        for(size_t x = 0; x < VGA_SCREEN_WIDTH; ++x) {
            uint16_t* const loc = vga_text_base_address + (y * VGA_SCREEN_WIDTH + x);
            *loc = *(loc + diff);
        }
    }

    for (size_t y = VGA_SCREEN_HEIGHT-n; y < VGA_SCREEN_HEIGHT; ++y) {
        for(size_t x = 0; x < VGA_SCREEN_WIDTH; ++x) {
            uint16_t* const loc = vga_text_base_address + (y * VGA_SCREEN_WIDTH + x);
            *loc = 0;
        }
    }
}

void vga_text_write(const vga_text_control* v, char c){
    uint16_t* const loc = vga_text_base_address + (v->cursor.y * VGA_SCREEN_WIDTH + v->cursor.x);

    *loc = (uint16_t) c | (uint16_t)((v->color.foreground & 0xF) << 8)
                        | (uint16_t)((v->color.background & 0xF) << 12);
}
