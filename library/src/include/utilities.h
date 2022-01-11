//
// Created by Frityet on 2022-01-01.
//

#ifndef UNIGS_SERVER_UTILITIES_
#define UNIGS_SERVER_UTILITIES_

#include "common.h"
#include <netdb.h>

#define NEW(_type) alloc_or_kablooey(sizeof(_type), LINE_AND_FILE)

ATTRIBUTE(malloc)
void *alloc_or_kablooey(size_t size, int line, const char *file);

char *int_to_str(int64_t num);

#endif //UNIGS_SERVER_UTILITIES_
