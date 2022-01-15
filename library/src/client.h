//
// Created by Frityet on 2022-01-10.
//

#ifndef UNIGS_SERVER_CLIENT_
#define UNIGS_SERVER_CLIENT_

#include <time.h>

#include "unigs_types.h"
#include "ipv4.h"

struct client {
    ipv4_t              address;
    struct addrinfo     *address_info;
    filedescriptor_t    socket;
    uint64_t            guid;
    time_t              connection_time;
    size_t              index;
    struct client       *next, *previous;
};

struct client_list {
    size_t          client_count;
    struct client   *head;
};

struct client *add_client(struct client_list *list, ipv4_t address, filedescriptor_t socket);
struct client *find_client(struct client_list *list, uint64_t guid);
void remove_client(struct client_list *list, uint64_t guid);
void free_client_list(struct client_list *list);

#endif //UNIGS_SERVER_CLIENT_
