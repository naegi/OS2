global idt_setup

idtr: 
    dw 0 ; limit 
    dd 0 ; base

idt_setup:;(void* idt, size_t limit)
    ; fill idt
    mov ax, [esp + 8]
    mov [idtr], ax
    mov eax, [esp + 4]
    mov [idtr+2], eax

    lidt [idtr]
    ret



%macro int_gate_no_arg 2
global int_gate_ %+ %1
int_gate_ %+ %1 :
    push byte 0 ; Arg will be 0 -- See intel 3.6.13 for 
                 ; signification of err code
    pushad ; eax, ecx, edx, original esp, ebp, esi, edi
    push gs
    push fs
    push es
    push ds

    cld ; DF should be cleared (sysV ABI)

    call %2

    pop ds
    pop es
    pop fs
    pop gs
    popad 
    add esp, 4
    iret
%endmacro

%macro int_gate_arg 2
global int_gate_ %+ %1
int_gate_ %+ %1 :
    pushad ; eax, ecx, edx, ebx, original esp, ebp, esi, edi
    push gs
    push fs
    push es
    push ds
    ; TODO: set kernel data segment
    cld ; DF should be cleared (sysV ABI)

    call %2

    pop ds
    pop es
    pop fs
    pop gs
    popad 
    iret
%endmacro

extern bpoint

int_gate_no_arg 0,  bpoint
int_gate_no_arg 1,  bpoint
int_gate_no_arg 2,  bpoint
int_gate_no_arg 3,  bpoint
int_gate_no_arg 4,  bpoint
int_gate_no_arg 5,  bpoint
int_gate_no_arg 6,  bpoint
int_gate_no_arg 7,  bpoint
int_gate_arg    8,  bpoint
int_gate_no_arg 9,  bpoint
int_gate_arg    10, bpoint
int_gate_arg    11, bpoint
int_gate_arg    12, bpoint
int_gate_arg    13, bpoint
int_gate_arg    14, bpoint

int_gate_no_arg 16, bpoint
int_gate_arg    17, bpoint
int_gate_no_arg 18, bpoint
int_gate_no_arg 19, bpoint
int_gate_no_arg 20, bpoint
int_gate_arg    21, bpoint
