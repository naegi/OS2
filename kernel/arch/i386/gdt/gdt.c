#include <libk/utils.h>
#include <kernel/i386/tss.h>
#include <kernel/i386/gdt.h>

// Flat memory map to start with
// TODO: Change to higher half
// TODO: Make a 2 staged kernel: a first stage (which is sized restricted) will setup memory management then the second stage is loaded
// We might even be able to load stage 2 kernel from disk => µ-kernel ?

// TODO: /!\ ! Is hardcoded !
static uint64_t gdt[6]; // We will go for 3 entry for now

// See INTEL manual 3.4.4, figure 3.8 for flags. 12 bits are usables, first (LSB) 8 bits are bits 8-16 of the 2nd double word
// bits 9-12 are bits 20-24

typedef struct{
    uint32_t base;
    uint32_t limit;
    uint16_t flags;
} segment_descriptor_t;

static void gdt_encode(segment_descriptor_t entry, uint64_t* gdt_entry){
    *gdt_entry = 0;
    uint16_t *loc= (uint16_t*)gdt_entry;
    loc[0] = (entry.limit & 0xFFFF);
    loc[1] = (entry.base & 0xFFFF);

    loc[2] = (entry.base >> 16 & 0xFF);
    loc[2] |= (entry.flags & 0xFF) << 8;

    loc[3] = (entry.limit >> 16 & 0xF);
    loc[3] |= (entry.flags >> 8 & 0xF) << 4;
    loc[3] |= (entry.base >> 24 & 0xFF) << 8;
}

void gdt_init(){

    gdt_encode((segment_descriptor_t){.base=0, .limit=0, .flags=0}, gdt); // null segment descriptor
    gdt_encode((segment_descriptor_t){ // code segment descriptor 0x08 (8*8 = 64)
            .base=0,
            .limit=0xFFFFFFFF,//*4kb = 4Go
            .flags=0xC9A // Granularity = 4kb, 32bits, present, ring 0, code execute/read
            }, gdt+1);
    gdt_encode((segment_descriptor_t){ // data segment descriptor 0x10
            .base=0,
            .limit=0xFFFFFFFF,//*4kb = 4Go
            .flags=0xC92 // Granularity = 4kb, 32bits, present, ring 0, data read/write
            }, gdt+2);
    gdt_encode((segment_descriptor_t){ // User's data segment descriptor 0x18
            .base=0,
            .limit=0xFFFFFFFF,//*4kb = 4Go
            .flags=0xCFA // Granularity = 4kb, 32bits, present, code execute/read
            }, gdt+3);
    gdt_encode((segment_descriptor_t){ // User's data segment descriptor 0x20
            .base=0,
            .limit=0xFFFFFFFF,//*4kb = 4Go
            .flags=0xCF2 // Granularity = 4kb, 32bits, present, data read/write
            }, gdt+4);

    void* addr = tss_setup(0x10);

    gdt_encode((segment_descriptor_t){ // TSS 0x28
            .base=(uint32_t)addr,
            .limit=(uint32_t)sizeof(tss_entry_t),
            .flags=0xE9
            }, gdt+5);
    gdt_setup((void*)gdt, sizeof gdt);

    reload_segments();
    tss_flush(0x2B);
}
