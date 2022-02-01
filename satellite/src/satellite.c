//
// Created by Frityet on 2022-02-01.
//

#include "satellite.h"

#include <stdio.h>

#include <logger.h>

#include "satellite_common.h"

#define EXCUSE(_action) LOG_ERROR("Could not " _action "!\nReason: %s", strerror(errno))

static void satellite_start(struct job_args *args)
{
    struct satellite
}

struct satellite create_satellite(uint16_t port)
{
    struct satellite satellite = {
        .port = port,
        .socket = -1,
        .callbacks = {
            .packet_received = NULL
        }
    };

    struct addrinfo hint = {0};
    hint.ai_family      = AF_INET;
    hint.ai_socktype    = SOCK_DGRAM;
    hint.ai_flags       = AI_PASSIVE;

    char portstr[5] = {0};
    sprintf(portstr, "%d", port);

    int status;
    if ((status = getaddrinfo(NULL, portstr, &hint, &satellite.addrinfo)) != 0) {
        LOG_ERROR("Could not get address info on port %s!\nError: %s", portstr, gai_strerror(status));
        return EMPTY(struct satellite);
    }

    satellite.socket = socket(satellite.addrinfo->ai_family, satellite.addrinfo->ai_socktype, satellite.addrinfo->ai_protocol);
    if (satellite.socket == -1) {
//        LOG_ERROR("Could not get socket!\nReason: %s", strerror(errno));
        EXCUSE("get socket");
        return EMPTY(struct satellite);
    }

    if (bind(satellite.socket, satellite.addrinfo->ai_addr, satellite.addrinfo->ai_protocol) != 0) {
//        LOG_ERROR("Could not bind socket!\nReason: %s", strerror(errno));
        EXCUSE("bind socket");
        return EMPTY(struct satellite);
    }

    if (listen(satellite.socket, 16) != 0) {
//        LOG_ERROR("Could not listen on socket!\nReason: %s", strerror(errno));
        EXCUSE("listen on socket");
        return EMPTY(struct satellite);
    }

    satellite.worker = employ_worker(satellite_start, JOB_ARGS(&satellite, NULL), NULL, NULL);

    return satellite;
}
