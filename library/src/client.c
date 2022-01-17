//
// Created by Frityet on 2022-01-10.
//

#include "client.h"

#include <libcommon.h>
#include <stdlib.h>
#include <unistd.h>

ATTRIBUTE(constructor(0)) void seed_rand_ctor(void)
{
    //TODO: Clang tidy warn?
    srand(time(0));
}

local uint64_t generate_guid(struct client_list list)
{
    uint64_t guid = random();

    struct client *node = list.head;
    while (node != NULL) {
        if (node->guid == guid) {
            return generate_guid(list);
        } else {
            node = node->next;
        }
    }
    return guid;
}

local struct client *get_tail(struct client_list list)
{
    struct client *node = list.head;
    while (node->next != NULL) {
        node = node->next;
    }
    return node;
}

local struct client *new_client(ipv4_t address, filedescriptor_t socket, uint64_t guid)
{
    struct client *ret = NEW(struct client);
    ret->address = address;
    ret->socket = socket;
    ret->guid = guid;
    ret->connection_time = time(0);
    ret->next = NULL;
    return ret;
}

struct client *add_client(struct client_list *list, ipv4_t address, filedescriptor_t socket)
{
    struct client   *new = new_client(address, socket, generate_guid(*list)),
                    *last = get_tail(*list);
    last->next = new;
    last->next->previous = last;
    list->client_count++;
    return new;
}

struct client *find_client(struct client_list *list, uint64_t guid)
{
    struct client *node = list->head;
    while (node->next != NULL) {
        if (node->guid == guid) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

void remove_client(struct client_list *list, uint64_t guid)
{
    struct client *deaths_row_inmate = find_client(list, guid);

    //You can't delete head!
    if (deaths_row_inmate == NULL || deaths_row_inmate->previous == NULL) {
        return;
    }

    struct client   *next = deaths_row_inmate->next,
                    *previous = deaths_row_inmate->previous;

    if (next == NULL) {
        previous->next = NULL;
        return;
    } else {
        previous->next = next;
    }
    next->previous = previous;

    close(deaths_row_inmate->socket);
    free(deaths_row_inmate);
    list->client_count--;
}

void free_client_list(struct client_list *list)
{
    struct client *node = list->head;
    while (node != NULL) {
        close(node->socket);
        node = node->next;
        free(node->previous);
    }
}
