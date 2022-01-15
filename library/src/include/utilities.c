//
// Created by Frityet on 2022-01-01.
//

#include "utilities.h"
#include "logger.h"
#include <stdlib.h>
#include <stdio.h>

void *alloc_or_kablooey(size_t size, int line, const char *file)
{
    void *alloc = malloc(size);
    if (alloc == NULL) {
        char buf[4096];
        sprintf(buf, "[%s: %d] Could not allocate %zu bytes of memory!\nReason: %s", file, line, size, strerror(errno));
        logbase(buf, line, file,  LOG_COLOUR_FATAL, stderr);
        exit(EXIT_FAILURE);
    }
    return alloc;
}

