//
// Created by Frityet on 2022-01-10.
//

#ifndef UNIGS_SERVER_IPV4_
#define UNIGS_SERVER_IPV4_

#include <stdint.h>
#include <netdb.h>

typedef struct ipv4 {
    union {
        struct {
            uint8_t     byte0, byte1, byte2, byte3;
        } bytes;
        uint8_t address[4];
    };
    uint16_t    port;
} ipv4_t;

ipv4_t strtoipv4(const char *str);
ipv4_t addrinfotoipv4(struct addrinfo addrinfo);
ipv4_t sockaddrtoipv4(struct sockaddr sockaddr);

#endif //UNIGS_SERVER_IPV4_
