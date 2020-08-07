#ifndef I386_MEMORY_MANAGEMENT_H
#define I386_MEMORY_MANAGEMENT_H

#include <kernel/i386/multiboot.h>

void memory_management_init(multiboot_info_t*);
void* memory_management_get_block(void);
void memory_management_free_block(void* addr);

#endif
