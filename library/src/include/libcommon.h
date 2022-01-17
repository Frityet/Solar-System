//
// Created by Frityet on 2022-01-01.
//

#ifndef UNIGS_SERVER_UTILITIES_
#define UNIGS_SERVER_UTILITIES_

#include <common.h>
#include <netdb.h>

#define IPV4_ADDRESS(_byte0, _byte1, _byte2, _byte3, _port) (ipv4_t) { .address = { (_byte0), (_byte1), (_byte2), (_byte3) }, .port = (_port) }

char *int_to_str(int64_t num);

typedef int filedescriptor_t;

#endif //UNIGS_SERVER_UTILITIES_
