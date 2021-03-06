//
// Created by Frityet on 2022-01-16.
//

#ifndef SOLARSYSTEM_COMMON_UTILITIES_
#define SOLARSYSTEM_COMMON_UTILITIES_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
extern int errno;

#define local static

#define LINE_AND_FILE __LINE__, __FILE__

#ifndef __cplusplus
static const void *nullptr = NULL;
#endif

/* va_args_count. https://github.com/donmccaughey/va_args_count
 Copyright (c) 2014, Don McCaughey. All rights reserved.
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 - Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 - Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

/**
 * Gets argument count from a varadict macro
 */
#define VA_ARGS_COUNT(...) \
    VA_ARGS_SHIFT_COUNT_VALUES(__VA_ARGS__, VA_ARGS_COUNT_VALUES)


#define VA_ARGS_COUNT_VALUES \
                            63, 62, 61, 60, \
    59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
    49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
    39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
    29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
    19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
     9,  8,  7,  6,  5,  4,  3,  2,  1,  0

#define VA_ARGS_SELECT_COUNT_VALUE( \
       _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, _10, \
      _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
      _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
      _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
      _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
      _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
      _61, _62, _63, \
        N, ... \
    ) \
      N

#define VA_ARGS_SHIFT_COUNT_VALUES(...) \
    VA_ARGS_SELECT_COUNT_VALUE(__VA_ARGS__)

/* END */

#define ATTRIBUTE(...) __attribute__((__VA_ARGS__))

#define _STRMACRO(_macro) #_macro
#define STRMACRO(_macro) _STRMACRO(_macro)

#define EMPTY(_type) (_type){0}

#define NEW(_type) memset(alloc_or_kablooey(sizeof(_type), LINE_AND_FILE), 0, sizeof(_type))

ATTRIBUTE(malloc, unused)
static void *alloc_or_kablooey(size_t size, int line, const char *file)
{
    void *alloc = malloc(size);
    if (alloc == NULL) {
        fprintf(stderr, "[%s:%d] Could not allocate %zu bytes of memory!\nReason: %s", file, line, size, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return alloc;
}

static inline uint32_t round_to_2nd_power(uint32_t num)
{
    num--;
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    num++;

    return num;
}

#endif //SOLARSYSTEM_COMMON_UTILITIES_
