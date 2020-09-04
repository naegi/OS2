
; Declare constants for the multiboot header.
MBALIGN  equ  1<<0              ; align loaded modules on page boundaries
MEMINFO  equ  1<<1              ; provide memory map
FLAGS    equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot

PAGING_FLAGS equ 0x83 ; Present, RW, size of 4MB

section .multiboot.data
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
align 4096
boot_page_directory:
resb 4096

section .bss
stack_bottom:
resb 16384
stack_top:
global stack_top

section .multiboot.text
global _start:function (_start.end - _start)
_start:
    ; No inter, no pagination here.
    ; First, setup pagination
    ; then, setup a stack and jump to higher half !

    ; setup a stack
    mov esp, stack_top
    sub esp, 0xC0000000

    ; save multiboot info datastructures and magic
    push eax
    push ebx

    ; identity map first 8MB
    xor eax, eax
    or eax, PAGING_FLAGS
    mov [boot_page_directory], eax

    add eax, 1 << 22
    mov [boot_page_directory+4], eax

    ; allow 4MB pages
    mov eax, cr4
    or eax, 0x10 ; set PSE (bit 4)  = 4 Mb page size
    mov cr4, eax

    ; startup pagination
    mov edx, boot_page_directory
    mov cr3, edx


    mov eax, cr0
    or eax, 0x80000000 ; set PG (bit 31) PE should already be set (bit 1)
    mov cr0, eax


    ; map kernel to 0XC0000000
    extern start_kernel
    extern end_kernel

    mov ebx, end_kernel
    mov eax, start_kernel

    sub ebx, eax
    shr ebx, 22 ; number of page to map

    shr eax, 22 ; first page to map

fill:

    lea ecx, [eax+ebx]

    mov edx, ecx
    shl edx, 22 ; first page to map
    sub edx, 0xC0000000
    or edx, PAGING_FLAGS ; physical index

    mov [boot_page_directory + 4*ecx] , edx

    dec ebx
    test ebx, ebx
    je fill

    ; far jump to finalise paging
    lea ecx, page_install
    jmp ecx

page_install:


    ; Now stack is also in higher half
    add esp, 0xC0000000

    extern kernel_early
    extern kernel_main


    ; already done before pagination
    ; push eax ; magic == 0x2BADB002
    ; push ebx ; multiboot_info struct passed by multiboot bootloader TODO: copy multiboot data ! It works only bc we still identity map the 8 first MB
    call kernel_early

    cli
halt:
    hlt
    jmp halt
_start.end:
