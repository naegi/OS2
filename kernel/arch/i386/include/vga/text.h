#ifndef I386_VGA_TEXT_H
#define I386_VGA_TEXT_H

/*
 * This is the low level vga text driver. See vga/vt100.h for a higher level console.
 */

#include <libk/utils.h>

#define VGA_SCREEN_HEIGHT 25
#define VGA_SCREEN_WIDTH 80

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

typedef struct{
    struct{
        uint8_t x, y;
    }cursor;
    struct{
        uint8_t background, foreground;
    }color;
} vga_text_control_t;

void vga_text_write(const vga_text_control_t*, char);
void vga_text_clear(void);
void vga_text_scroll(uint8_t);

#endif /* ifndef I386_VGA_TEXT_H */
