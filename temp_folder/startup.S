/* Starup file for microcontroller */

.cpu cortex-m4
.thumb

/* Thumb and ARM instructions use same syntax */
.syntax unified

/* Interrupt vector table */
.section isr_vector
.word 0x20020000 /* Stack pointer reset value */
.word _start    /* 1 Reset */
.word _hang     /* 2 NMI */
.word _hang     /* 3 Hard fault */
.word _hang     /* 4 Memory management fault */
.word _hang     /* 5 Bus fault */
.word _hang     /* 6 Usage fault */
.word _hang     /* 7 RESERVED */
.word _hang     /* 8 RESERVED */
.word _hang     /* 9 RESERVED */
.word _hang     /* 10 RESERVED */
.word _hang     /* 11 SVCall */
.word _hang     /* 12 Debug */
.word _hang     /* 13 RESERVED */
.word _hang     /* 14 PendSV */
.word _hang     /* 15 Systick */
.word _hang     /* 16 IRQ0 */

.thumb_func
.global _start
_start:
    bl main
    b _hang

.thumb_func
_hang:
    b .

/* Choose to use internal RC oscillator or external clock source (probably) */
/* Set prescalers for AHB high-speed  and low-speed APB buses */

.end
