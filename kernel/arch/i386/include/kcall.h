#ifndef I386_KCALL_H
#define I386_KCALL_H

#include <libk/utils.h>
#include <kernel/i386/regs.h>

#define KCALL_WRITE 0x4
#define KCALL_MMAP 0x90
#define KCALL_UNMMAP 0x91

void kcall_init(void);
void ASM kcall_handler_asm(void);
void kcall_handler_(regs_t regs);

void ASM kcall(uint32_t kcall_no, void* data);

typedef struct {
    int fd;
    const void *buf;
    size_t count;
} kcall_write_t;


typedef struct {
    void* addr;
    size_t length;
    int prot; // Unimplemente, same as PROT_READ | PROT_WRITE | PROT_EXEC
    int flags;
    int fd; // Unimplemented
    size_t offset; // Unimplemented
} kcall_mmap_t;

typedef struct {
    void* addr;
    size_t length;
} kcall_unmmap_t;
#endif /* ifndef I386_KCALL_H */
