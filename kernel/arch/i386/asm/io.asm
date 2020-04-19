global inb
global ind
global inw

global outb
global outd
global outw

outb:
    mov dx, [esp + 4] ; port number
    mov al, [esp + 8] ; data
    out dx, al
    ret

outd:
    mov dx, [esp + 4] ; port number
    mov ax, [esp + 8] ; data
    out dx, ax
    ret

outw:
    mov dx, [esp + 4] ; port number
    mov eax, [esp + 8] ; data
    out dx, eax
    ret

inb:
    mov dx, [esp + 4] ; port number
    in al, dx 
    ret ; data is in eax

ind:
    mov dx, [esp + 4] ; port number
    in ax, dx 
    ret ; data is in eax

inw:
    mov dx, [esp + 4] ; port number
    in eax, dx 
    ret ; data is in eax

