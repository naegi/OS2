#ifndef PROCESS_H
#define PROCESS_H
#include <kernel/i386/kcall.h>

typedef struct process {
    regs_t regs;
    uint32_t cr3;
    struct process *next;
} process_t;

void process_init(void);

void process_create(void* entry_point);

// Current process let the hand to next process
void process_yield_current(regs_t* regs);

void process_start(void);
void process_jump(void* entry_point, void* cr3, void* useresp);

#endif /* ifndef PROCESS_H */
