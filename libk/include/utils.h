#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define UNUSED(x) (void)(x)
#define NOP (void)0
#define GET_BYTE(x, y) ((x) >> (8 * (y)) & 0xFF)
#define ASM __cdecl

size_t itoa_buffsize(int x, unsigned int base);
void itoa(int x, char* buff, unsigned int base);

#endif /* ifndef UTILS_H */
