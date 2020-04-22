ENTRY(_start)

SECTIONS
{
    . = 1M; /* Put everything at 1Mb to start with */
    start_kernel = ALIGN(4K);

    /* Section format: 
     * section start : end
     * */

    /* First put multiboot headers (needed) then put all code*/
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    /* Read only data */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /* RW data (initialized) */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }
    /* Read-write data (uninitialized) and stack */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        page_directory_kernel = ALIGN(4K);
        *(COMMON)
        *(.bss)
        *(.bootstrap_stack)
    }

    end_kernel = ALIGN(4K);
}
