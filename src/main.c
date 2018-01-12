// Freestanding header files
// <float.h> <iso646.h> <limits.h> <stdarg.h> <stdbool.h> <stddef.h> <stdint.h>

#include "mmu.h"

int
main( void )
{
    char src[10] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
    char dst[10];

    memcpy( dst, src, 10 );

    return 0;
}
