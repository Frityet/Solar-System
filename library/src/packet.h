//
// Created by Frityet on 2022-01-10.
//

#ifndef UNIGS_SERVER_PACKET_
#define UNIGS_SERVER_PACKET_

#include <common.h>

struct packet {
    byte_t          *data;
    size_t          data_size;
    struct packet   *next_packet;
};

struct packet_list {
    size_t          length;
    struct packet   *head, *recent;
};


struct packet *add_packet(struct packet_list *list, byte_t *data, size_t data_size);

#endif //UNIGS_SERVER_PACKET_
