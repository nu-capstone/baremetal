#ifndef MMU_H
#define MMU_H

#include "stddef.h"

void *memcpy( void *dst, void const *src, size_t len );
void *memmove( void *dst, const void *src, size_t len );
void *memset( void *s, int c, size_t len );
void *memcmp( const void *s1, const void *s2, size_t len );

#endif // MMU_H
