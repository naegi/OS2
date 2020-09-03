#ifndef UTILS_H
#define UTILS_H
#include <stdnoreturn.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define UNUSED(x) (void)(x)
#define NOP (void)0
#define GET_BYTE(x, y) ((x) >> (8 * (y)) & 0xFF)
#define ALIGN(a, x) ((a  + (x) - 1) & ~((size_t)(x) - 1)) // Same definition as for ld linker. x should be a power of 2
#define SIZE_MB(start, end)  (ALIGN(end - start, 1 << 20) >> 20)
#define SIZE_KB(start, end)  (ALIGN(end - start, 1 << 10) >> 10)
#define ASM __cdecl

size_t uitoa_buffsize(unsigned int x, unsigned int base);
void uitoa(unsigned int x, char* buff, unsigned int base);
size_t itoa_buffsize(int x, unsigned int base);
void itoa(int x, char* buff, unsigned int base);
int atoi(char* x);

noreturn void halt(void);

#endif /* ifndef UTILS_H */
