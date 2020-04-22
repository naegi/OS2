global enable_PSE
global paging_setup

paging_setup:
    ; TODO: Use cpuid to check wether all features are available or not
    mov eax, cr4
    or eax, 0x10 ; set PSE (bit 4)
    mov cr4, eax

    mov eax, [esp+4]
    mov cr3, eax
    
    mov eax, cr0
    or eax, 0x80000000 ; set PG (bit 31) PE should already be set (bit 1)
    mov cr0, eax
    
    ret
