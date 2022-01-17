//
// Created by Frityet on 2022-01-13.
//

#ifndef UNIGS_UNIGS_TYPES_
#define UNIGS_UNIGS_TYPES_

#include <stddef.h>
#include <stdint.h>

/**
 * Byte - unsigned char
 */
typedef uint8_t     byte_t;

/**
 * UNIX file descriptor - int32
 */
typedef int32_t     filedescriptor_t;


/**
 * Unicode string - unsigned int32 pointer
 */
typedef uint32_t    *ustring_t;

#ifdef bool
#undef bool
#endif
/**
 * Bool, but a typedef
 */
typedef enum { TRUE = 1, FALSE = 0 } bool;

#define atomic _Atomic

#endif //UNIGS_UNIGS_TYPES_
