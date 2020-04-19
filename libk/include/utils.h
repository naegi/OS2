#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define UNUSED(x) (void)(x)
#define GET_BYTE(x, y) ((x) >> (8 * (y)) & 0xFF)
#define ASM __cdecl

#endif /* ifndef UTILS_H */
