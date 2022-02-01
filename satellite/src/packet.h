//
// Created by Frityet on 2022-02-01.
//

#ifndef SOLARSYSTEM_PACKET_
#define SOLARSYSTEM_PACKET_

#include <solarsystem_types.h>

struct packet {
    size_t  size;
    byte_t  *bytes;
};

#endif //SOLARSYSTEM_PACKET_
