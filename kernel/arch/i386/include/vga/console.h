#ifndef I386_VGA_CONSOLE
#define I386_VGA_CONSOLE

/*
 * Emulate V100 Terminal on VGA text output
 * */

#include <libk/utils.h>

// Write buffer to vga output
void vga_console_init(void);
void vga_console_reset(void);
void vga_console_write(const void* buf, size_t nbyte);
void vga_console_puts(const char *s);
void vga_console_putchar(char c);

#endif /* ifndef I386_VGA_CONSOLE */
