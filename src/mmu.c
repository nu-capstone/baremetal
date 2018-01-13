/******************************************************************************
 * Memory management
 */

#include "global_defines.h"
#include "mmu.h"

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
    while ( !((size_t) pcsrc & 0x3) && !((size_t) pcdst & 0x3) && len > 0 ) 
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
    unsigned char *pcdst = ( unsigned char* ) dst;
    unsigned char *pcsrc = ( unsigned char* ) src;

    if ( pcdst == pcsrc )
        return pcdst;

    // if start of pcdst is in pdsrc copy from end
    else if ( pcdst >= pcsrc && pcdst <= pcsrc + len )
    {         
        while ( len > 0 )
        {
        }
    }

    // if end of pcdst is in pdsrc copy from beginning
    else if ( pcdst + len >= pcsrc && pcdst <= pcsrc)
    {
    
    }

    // else use memcpy
    else
        memcpy( dst, src, len );
}
