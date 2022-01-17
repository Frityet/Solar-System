//
// Created by Frityet on 2022-01-16.
//

#ifndef UNIGS_CLIENT_
#define UNIGS_CLIENT_

#include <unigs_types.h>

struct client {
    filedescriptor_t    socket;
    size_t              id;
    struct client       *next_client;
};

struct client_list {
    size_t          client_count;
    struct client   *head;
};

struct client_list *create_clientlist(filedescriptor_t socket);
struct client *add_client(struct client_list *list, filedescriptor_t socket);
void remove_client(struct client_list *list, int index);
void free_clientlist(struct client_list *list);

#endif //UNIGS_CLIENT_
