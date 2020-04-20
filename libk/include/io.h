#ifndef LIBK_IO_H
#define LIBK_IO_H

#include <stdarg.h>

// TODO: return type should be changed

void puts(const char*);
void putchar(char);

void printfk(const char*, ...);
void vprintfk(const char*, va_list);
void snprintfk(char*, const char*, ...);
void vsnprintfk(char*, const char*, va_list);

#endif /* ifndef LIBK_IO_H */
