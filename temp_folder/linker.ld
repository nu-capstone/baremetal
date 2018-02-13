/******************************************************************************
 * Linker script
 */

EXTERN(_start)

/* Will probably need to change for SD card */
MEMORY
{
    flash(rx) : ORIGIN = 0x08000000, LENGTH = 1M
    ram(xrw)  : ORIGIN = 0x20000000, LENGTH = 192K
}

SECTIONS
{
    . = 0x0;
    .reset : { *(.isr_vector) } > ram

    .text : {
        *(.text)
    }
}
