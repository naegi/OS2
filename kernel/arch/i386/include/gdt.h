#ifndef I386_GDT
#define I386_GDT

#include <libk/utils.h>

void gdt_init(void);
void ASM gdt_setup(void*, size_t);
void ASM reload_segments(void);
#endif /* ifndef I386_GDT */
