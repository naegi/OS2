global kcall_handler_asm
extern kcall_handler_

kcall_handler_asm:
    ; interrupt code should be in eax
    ; ptr to data in user space should be in ebx
    push byte 0
                
    pushad ; eax, ecx, edx, ebx, original esp, ebp, esi, edi
    push gs
    push fs
    push es
    push ds

    cld

    call kcall_handler_

    pop ds
    pop es
    pop fs
    pop gs
    popad 
    add esp, 4
    
    iret

global kcall
kcall:
    push ebp
    mov ebp, esp
    push ebx

    mov eax, [ebp+0x8]
    mov ebx, [ebp+0xC]
    int 0x80

    pop ebx 
    pop ebp 
    ret
