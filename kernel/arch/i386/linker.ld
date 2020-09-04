ENTRY(_start)

SECTIONS
{
    . = 1M; /* Put everything at 1Mb to start with */
    .multiboot.data : {
        *(.multiboot.data)

    }

    .multiboot.text : {
        *(.multiboot.text)
    }


    /* We go for higher half kernel. */
    . += 0xC0000000;
    start_kernel = ALIGN(4K);
    .text BLOCK(4K) : AT( ADDR (.text) - 0xC0000000 )
    {
        *(.text)
    }

    /* Read only data */
    .rodata BLOCK(4K) : AT( ADDR (.rodata) - 0xC0000000 )
    {
        *(.rodata)
    }

    /* RW data (initialized) */
    .data BLOCK(4K) : AT( ADDR (.data) - 0xC0000000 )
    {
        *(.data)
    }
    /* Read-write data (uninitialized) and stack */
    .bss BLOCK(4K) :  AT( ADDR (.bss) - 0xC0000000 )
    {
        *(COMMON)
        *(.bss)
    }

    end_kernel = ALIGN(4K);
}
