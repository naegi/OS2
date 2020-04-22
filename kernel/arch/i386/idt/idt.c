#include <libk/utils.h>

#include <kernel/i386/idt.h>


#define IDT_SIZE 32

static uint64_t idt[IDT_SIZE];

struct task_gate_descriptor{
    uint16_t tss_segment_selector;
    uint8_t flags;
};

struct interrupt_gate_descriptor{
    uint32_t offset;
    uint16_t segment_selector; // Code selector
    uint8_t flags; // See intel manual Volume 3 figure 6.2 -- the 3 LSB are considered: 1 for P and 2 for DPL
};

static void encode_interrupt_gate(uint64_t* idt_entry, struct interrupt_gate_descriptor descr, bool is_trap_gate){
    uint16_t *loc = (uint16_t*)idt_entry;
    loc[0] = descr.offset & 0xFFFF;
    loc[1] = descr.segment_selector;
    loc[2] = 0xe00; // Type = interrupt gate
    loc[2] |= (uint16_t)((descr.flags & 0x7) << 13);
    loc[2] |= ((is_trap_gate) & 0x1) << 8;
    loc[3] = (descr.offset & 0xFFFF0000) >> 16;
}

void idt_init(){
    struct interrupt_gate_descriptor gate_not_used = {.offset=0, .segment_selector=0, .flags=0};
    // See Volume 3 table 6.1 for list of exceptions and interrupts

    // Segment is 0x08 (code segment)
    // flags are present, ring 0 => 0b100 = 0x4
    encode_interrupt_gate(idt + 0,  (struct interrupt_gate_descriptor){ //Divide error
            .offset=(uint32_t)int_gate_0,  .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 1,  (struct interrupt_gate_descriptor){ // Debug Exception
            .offset=(uint32_t)int_gate_1,  .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 2,  (struct interrupt_gate_descriptor){ // NMI Interrupt
            .offset=(uint32_t)int_gate_2,  .segment_selector=0x08,.flags=0x04}, false); // Interrupt, not fault ?
    encode_interrupt_gate(idt + 3,  (struct interrupt_gate_descriptor){ // Breakpoint
            .offset=(uint32_t)int_gate_3,  .segment_selector=0x08,.flags=0x04}, true);
    encode_interrupt_gate(idt + 4,  (struct interrupt_gate_descriptor){ // Overflow
            .offset=(uint32_t)int_gate_4,  .segment_selector=0x08,.flags=0x04}, true);
    encode_interrupt_gate(idt + 5,  (struct interrupt_gate_descriptor){ // Bound range Exceeded
            .offset=(uint32_t)int_gate_5,  .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 6,  (struct interrupt_gate_descriptor){ // Invalid opcode
            .offset=(uint32_t)int_gate_6,  .segment_selector=0x08,.flags=0x04}, true);
    encode_interrupt_gate(idt + 7,  (struct interrupt_gate_descriptor){ // Device Not Available (Math coproc)
            .offset=(uint32_t)int_gate_7,  .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 8,  (struct interrupt_gate_descriptor){ // Double fault
            .offset=(uint32_t)int_gate_8,  .segment_selector=0x08,.flags=0x04}, false); // (abort)
    encode_interrupt_gate(idt + 9,  (struct interrupt_gate_descriptor){ // Coproc segment overrun (will never occur)
            .offset=(uint32_t)int_gate_9,  .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 10, (struct interrupt_gate_descriptor){ //Invalid TSS
            .offset=(uint32_t)int_gate_10, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 11, (struct interrupt_gate_descriptor){ // Segment not present
            .offset=(uint32_t)int_gate_11, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 12, (struct interrupt_gate_descriptor){ // Stack segment fault
            .offset=(uint32_t)int_gate_12, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 13, (struct interrupt_gate_descriptor){ // General protection
            .offset=(uint32_t)int_gate_13, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 14, (struct interrupt_gate_descriptor){ // Page Fault
            .offset=(uint32_t)int_gate_14, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 15, gate_not_used, false); // Intel reserved. Do not use.
    encode_interrupt_gate(idt + 16, (struct interrupt_gate_descriptor){ // x87 FPU Floating point Error (Math fault)
            .offset=(uint32_t)int_gate_16, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 17, (struct interrupt_gate_descriptor){ // Alignement Check
            .offset=(uint32_t)int_gate_17, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 18, (struct interrupt_gate_descriptor){ // Machine check
            .offset=(uint32_t)int_gate_18, .segment_selector=0x08,.flags=0x04}, false); // (abort)
    encode_interrupt_gate(idt + 19, (struct interrupt_gate_descriptor){ // SIMD Floating-point exception
            .offset=(uint32_t)int_gate_19, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 20, (struct interrupt_gate_descriptor){ // Virtualization exception d
            .offset=(uint32_t)int_gate_20, .segment_selector=0x08,.flags=0x04}, false);
    encode_interrupt_gate(idt + 21, (struct interrupt_gate_descriptor){ // Control protection Exception
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
