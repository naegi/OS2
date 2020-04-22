global gdt_setup
global reload_segments

gdtr:
    dw 0 ; limit
    dd 0 ; base

gdt_setup:;(void* gdt, size_t limit)
    ; fill gdtr
    mov eax, [esp + 4]
    mov [gdtr + 2], eax
    mov ax, [esp + 8]
    mov [gdtr], ax

    lgdt [gdtr] 
    ret

reload_segments:
    jmp 0x08:reload_CS
reload_CS:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret

