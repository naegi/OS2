#include <libk/utils.h>

#include <kernel/i386/idt.h>


#define IDT_SIZE 32

static uint64_t idt[IDT_SIZE];

typedef struct{
    uint16_t tss_segment_selector;
    uint8_t flags;
} task_gate_descriptor_t;

typedef struct{
    uint32_t offset;
    uint16_t segment_selector; // Code selector
    uint8_t flags; // See intel manual Volume 3 figure 6.2 -- the 3 LSB are considered: 1 for P and 2 for DPL
}  interrupt_gate_descriptor_t;

static void encode_interrupt_gate(uint64_t* idt_entry, interrupt_gate_descriptor_t descr, bool is_trap_gate){
    uint16_t *loc = (uint16_t*)idt_entry;
    loc[0] = descr.offset & 0xFFFF;
    loc[1] = descr.segment_selector;
    loc[2] = 0xe00; // Type = interrupt gate
    loc[2] |= (uint16_t)((descr.flags & 0x7) << 13);
    loc[2] |= ((is_trap_gate) & 0x1) << 8;
    loc[3] = (descr.offset & 0xFFFF0000) >> 16;
}

void idt_init(){
    interrupt_gate_descriptor_t gate_not_used = {.offset=0, .segment_selector=0, .flags=0};
    // See Volume 3 table 6.1 for list of exceptions and interrupts

    // Segment is 0x08 (code segment)
    // flags are present, ring 0 => 0b100 = 0x4
    encode_interrupt_gate(idt + 0,  (interrupt_gate_descriptor_t){ //Divide error
            .offset=(uint32_t)int_gate_0,  .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 1,  (interrupt_gate_descriptor_t){ // Debug Exception
            .offset=(uint32_t)int_gate_1,  .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 2,  (interrupt_gate_descriptor_t){ // NMI Interrupt
            .offset=(uint32_t)int_gate_2,  .segment_selector=0x08,.flags=0x04}, false); // Interrupt, not fault ?
    encode_interrupt_gate(idt + 3,  (interrupt_gate_descriptor_t){ // Breakpoint
            .offset=(uint32_t)int_gate_3,  .segment_selector=0x08,.flags=0x04}, true);
    encode_interrupt_gate(idt + 4,  (interrupt_gate_descriptor_t){ // Overflow
            .offset=(uint32_t)int_gate_4,  .segment_selector=0x08,.flags=0x04}, true);
    encode_interrupt_gate(idt + 5,  (interrupt_gate_descriptor_t){ // Bound range Exceeded
            .offset=(uint32_t)int_gate_5,  .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 6,  (interrupt_gate_descriptor_t){ // Invalid opcode
            .offset=(uint32_t)int_gate_6,  .segment_selector=0x08,.flags=0x04}, true);
    encode_interrupt_gate(idt + 7,  (interrupt_gate_descriptor_t){ // Device Not Available (Math coproc)
            .offset=(uint32_t)int_gate_7,  .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 8,  (interrupt_gate_descriptor_t){ // Double fault
            .offset=(uint32_t)int_gate_8,  .segment_selector=0x08,.flags=0x04}, false); // (abort)
    encode_interrupt_gate(idt + 9,  (interrupt_gate_descriptor_t){ // Coproc segment overrun (will never occur)
            .offset=(uint32_t)int_gate_9,  .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 10, (interrupt_gate_descriptor_t){ //Invalid TSS
            .offset=(uint32_t)int_gate_10, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 11, (interrupt_gate_descriptor_t){ // Segment not present
            .offset=(uint32_t)int_gate_11, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 12, (interrupt_gate_descriptor_t){ // Stack segment fault
            .offset=(uint32_t)int_gate_12, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 13, (interrupt_gate_descriptor_t){ // General protection
            .offset=(uint32_t)int_gate_13, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 14, (interrupt_gate_descriptor_t){ // Page Fault
            .offset=(uint32_t)int_gate_14, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 15, gate_not_used, false); // Intel reserved. Do not use.
    encode_interrupt_gate(idt + 16, (interrupt_gate_descriptor_t){ // x87 FPU Floating point Error (Math fault)
            .offset=(uint32_t)int_gate_16, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 17, (interrupt_gate_descriptor_t){ // Alignement Check
            .offset=(uint32_t)int_gate_17, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 18, (interrupt_gate_descriptor_t){ // Machine check
            .offset=(uint32_t)int_gate_18, .segment_selector=0x08,.flags=0x04}, false); // (abort)
    encode_interrupt_gate(idt + 19, (interrupt_gate_descriptor_t){ // SIMD Floating-point exception
            .offset=(uint32_t)int_gate_19, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 20, (interrupt_gate_descriptor_t){ // Virtualization exception d
            .offset=(uint32_t)int_gate_20, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 21, (interrupt_gate_descriptor_t){ // Control protection Exception
            .offset=(uint32_t)int_gate_21, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 22, gate_not_used, false); // Intel reserved. Do not use.
    encode_interrupt_gate(idt + 23, gate_not_used, false); // Intel reserved. Do not use.
    encode_interrupt_gate(idt + 24, gate_not_used, false); // Intel reserved. Do not use.
    encode_interrupt_gate(idt + 25, gate_not_used, false); // Intel reserved. Do not use.
    encode_interrupt_gate(idt + 26, gate_not_used, false); // Intel reserved. Do not use.
    encode_interrupt_gate(idt + 27, gate_not_used, false); // Intel reserved. Do not use.
    encode_interrupt_gate(idt + 28, gate_not_used, false); // Intel reserved. Do not use.
    encode_interrupt_gate(idt + 29, gate_not_used, false); // Intel reserved. Do not use.
    encode_interrupt_gate(idt + 30, gate_not_used, false); // Intel reserved. Do not use.
    encode_interrupt_gate(idt + 31, gate_not_used, false); // Intel reserved. Do not use.

    idt_setup((void*)&idt, sizeof idt);
}
