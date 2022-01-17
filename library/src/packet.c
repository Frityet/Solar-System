//
// Created by Frityet on 2022-01-10.
//

#include "packet.h"

#include <libcommon.h>

struct packet *add_packet(struct packet_list *list, byte_t *data, size_t data_size)
{
    struct packet *head = list->head;
    while (head != NULL)
        head = head->next_packet;

    head = NEW(struct packet);

    head->data = data;
    head->data_size = data_size;

    return head;
}
