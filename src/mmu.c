/******************************************************************************
 * Memory management
 */

#include <mmu.h>

/******************************************************************************
 * Optimized memcpy for 32-bit copies
 */
void *
memcpy( void *dst,
        void const *src,
        size_t len )
{
    char *pcdst = (char *) dst;
    char *pcsrc = (char *) src;

    // while not 32-bit aligned do byte-by-byte copy
    while ( !(pcsrc & 0x3) && !(pcdst & 0x3) && len > 4 ) 
    {
        *pcdst++ = *pcsrc++;
        len--;
    }

    // XXX Do 4-byte copies
    
    // XXX Finish rest of the copies

    return dst;
}

/******************************************************************************
 * Optimized memmove using 32-bit copies where possible
 */
void *
memmove( void *dst,
         const void *src,
         size_t len )
{
    unsigned char *pbdst = ( unsigned char* ) dst;
    unsigned char *pbsrc = ( unsigned char* ) src;

    if ( pbdst == pdsrc )
        return pbdst;

    // if start of pbdst is in pdsrc copy from end
    else if ( pbdst >= pdsrc && pbdst =< pdsrc + len )
    {         
        while ( len > 0 )
        {
            if ( ) 
        }
    }

    // if end of pbdst is in pdsrc copy from beginning
    else if ( pbdst + len >= pdsrc && pbdst <= pdsrc)
    {
    
    }

    // else use memcpy
    else
        memcpy( dst, src, len );
}
