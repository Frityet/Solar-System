//
// Created by Frityet on 2021-12-31.
//

#ifndef UNIGS_SERVER_SERVER_
#define UNIGS_SERVER_SERVER_

#include <stdio.h>
#include <stdint.h>
#include <common.h>
#include <netdb.h>
#include <stdbool.h>

#include "packet.h"
#include "client.h"

#ifndef SERVER_MAX_QUEUE
    #define SERVER_MAX_QUEUE 16
#endif

struct server {
    ipv4_t              ip_address;
    uint32_t            player_count, max_players;
    struct addrinfo     *server_info;
    struct client_list  connected_players;
    filedescriptor_t    socket;
};

struct server server_initialise(uint16_t port);
filedescriptor_t server_accept_client(struct server *server);

#endif //UNIGS_SERVER_SERVER_
