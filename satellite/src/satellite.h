//
// Created by Frityet on 2022-02-01.
//

#ifndef SOLARSYSTEM_SATELLITE_
#define SOLARSYSTEM_SATELLITE_

#include <netdb.h>

#include <solarsystem_types.h>
#include <jobs.h>

#include "packet.h"

typedef void packet_received_f(struct packet *packet);

struct satellite {
    filedescriptor_t    socket;
    uint16_t            port;
    struct addrinfo     *addrinfo;
    struct worker       *worker;
    struct {
        packet_received_f *packet_received;
    } callbacks;
};

struct satellite create_satellite(uint16_t port);
static inline void free_satellite(struct satellite satellite)
{
    freeaddrinfo(satellite.addrinfo);
}


#endif //SOLARSYSTEM_SATELLITE_
