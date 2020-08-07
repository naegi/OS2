#ifndef LIBK_IO_H
#define LIBK_IO_H

#include <stdarg.h>
#include <libk/utils.h>

typedef struct {int fd;} FILE;


FILE* stdout;

// TODO: return type should be changed

int fputs(const char*, FILE*);
int puts(const char*);
int putchar(int);

void printfk(const char*, ...);
void vprintfk(const char*, va_list);
void snprintfk(char*, const char*, ...);
void vsnprintfk(char*, const char*, va_list);

size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);
#endif /* ifndef LIBK_IO_H */
