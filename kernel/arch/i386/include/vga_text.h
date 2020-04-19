#ifndef I386_VGA_TEXT_H
#define I386_VGA_TEXT_H

#include <libk/utils.h>

#define VGA_TEXT_COLOR_BLACK          0x0
#define VGA_TEXT_COLOR_BLUE           0x1
#define VGA_TEXT_COLOR_GREEN          0x2
#define VGA_TEXT_COLOR_CYAN           0x3
#define VGA_TEXT_COLOR_RED            0x4
#define VGA_TEXT_COLOR_MAGENTA        0x5
#define VGA_TEXT_COLOR_BROWN          0x6
#define VGA_TEXT_COLOR_LIGHT_GRAY     0x7
#define VGA_TEXT_COLOR_DARK_GRAY      0x8
#define VGA_TEXT_COLOR_LIGHT_BLUE     0x9
#define VGA_TEXT_COLOR_LIGHT_GREEN    0xA
#define VGA_TEXT_COLOR_LIGHT_CYAN     0xB
#define VGA_TEXT_COLOR_LIGHT_RED      0xC
#define VGA_TEXT_COLOR_LIGHT_MANGENTA 0xD
#define VGA_TEXT_COLOR_YELLOW         0xE
#define VGA_TEXT_COLOR_WHITE          0xF

void vga_text_init(void);

void vga_text_set_mode(uint8_t foreground_colour, uint8_t background_colour);

void vga_text_set_cursor_pos(uint8_t x, uint8_t y);
void vga_text_get_cursor_pos(uint8_t x, uint8_t y);


/* Cleanup screen */
void vga_text_clean(void);

/* Write *size* characters on vga_text*/
void vga_text_write(const char* c, size_t size);

void vga_text_putchar(char c);

#endif /* ifndef I386_VGA_TEXT_H */
