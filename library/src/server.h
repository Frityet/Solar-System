//
// Created by Frityet on 2022-01-16.
//

#ifndef UNIGS_SERVER_
#define UNIGS_SERVER_

#include <netdb.h>

#include <unigs_types.h>

#include "client.h"

struct server {
    filedescriptor_t    socket;
    uint16_t            port;
    size_t              connected_client_count;
    struct addrinfo     *address_info;
    struct client_list  connected_clients;
};

struct server create_server(uint16_t port);

struct client *wait_for_connection(struct server *server);

void free_server(struct server *server);


#endif //UNIGS_SERVER_
