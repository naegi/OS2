#ifndef I386_KCALL_H
#define I386_KCALL_H

#include <libk/utils.h>
#include <kernel/i386/regs.h>

void kcall_init(void);
void ASM kcall_handler_asm(void);
void kcall_handler_(regs_t regs);

void ASM kcall(uint32_t kcall_no, void* data);

#endif /* ifndef I386_KCALL_H */
