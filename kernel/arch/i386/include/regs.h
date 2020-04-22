#ifndef I386_ARCH_H
#define I386_ARCH_H

#include <libk/utils.h>

// See Intel Vol 3 fig. 6.4 for order (used in interrupts)
// Code should be manually pushed if no code were pushed by proco
// This is true bc, there IS a privilege level change (still look at 6.4)
typedef struct {
    uint32_t ds, es, fs, gs,
             edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t err_co, eip, cs, eflags, useresp, ss;
} __attribute__((packed)) regs_t;

#endif /* ifndef I386_ARCH_H */
