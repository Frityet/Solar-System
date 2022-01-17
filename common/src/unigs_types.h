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
 * String - const char pointer
 */
typedef const char  *string_t;

/**
 * Unicode string - unsigned int32 pointer
 */
typedef uint32_t    *ustring_t;

#ifdef bool
    #undef bool
#endif
#ifdef true
    #undef true
#endif
#ifdef false
    #undef false
#endif

/**
 * Bool, but a typedef
 */
typedef enum { TRUE = (_Bool)1, FALSE = (_Bool)0, true = (_Bool)1, false = (_Bool)0 } bool;

#define ATOMIC _Atomic

#endif //UNIGS_UNIGS_TYPES_
