#ifndef I386_SERIAL
#define I386_SERIAL

#include <libk/utils.h>

void serial_init(void);
void serial_write(const char*, size_t size);
void serial_putchar(char);
void serial_puts(const char*);
char serial_getchar(void);

#endif /* ifndef SYMBOL */
