#ifndef I386_IDT_H
#define I386_IDT_H

#include <libk/utils.h>

void interrupts_init(void);
void interrupts_install(size_t no, void* handler, bool user_available);
void idt_setup(void*, size_t);

void ASM int_gate_0(void);
void ASM int_gate_1(void);
void ASM int_gate_2(void);
void ASM int_gate_3(void);
void ASM int_gate_4(void);
void ASM int_gate_5(void);
void ASM int_gate_6(void);
void ASM int_gate_7(void);
void ASM int_gate_8(void);
void ASM int_gate_9(void);
void ASM int_gate_10(void);
void ASM int_gate_11(void);
void ASM int_gate_12(void);
void ASM int_gate_13(void);
void ASM int_gate_14(void);

void ASM int_gate_16(void);
void ASM int_gate_17(void);
void ASM int_gate_18(void);
void ASM int_gate_19(void);
void ASM int_gate_20(void);
void ASM int_gate_21(void);

#endif /* ifndef I386_IDT_H */
