#include <libk/string.h>

#include <kernel/i386/tss.h>

static tss_entry_t tss;

extern  void* stack_top;

void* tss_setup(uint32_t datasegment_descriptor){
    memset(&tss, 0, sizeof(tss_entry_t));
    tss.ss0 = datasegment_descriptor;
    tss.esp0 = (uint32_t)&stack_top; // reuse stack used to init kernel
    return &tss;
}
