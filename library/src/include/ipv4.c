//
// Created by Frityet on 2022-01-10.
//

#include "ipv4.h"

#include <stdio.h>

#include "logger.h"

ipv4_t strtoipv4(const char *str)
{
    ipv4_t ip = {0};
    char current_byte[3] = {0};
    int byte_index = 0, ipaddr_byte_index = 0;

    while (*str != '\0') {
        current_byte[byte_index] = *str;
        byte_index++;
        if (*str == '.') {
            byte_index = 0;
            snprintf(current_byte, 3, "%d", ip.address[ipaddr_byte_index]);
            ipaddr_byte_index++;
        }

        if (*str == ':') {
            char port_word[4] = {0};
            int port_index = 0;
            while (*str != '\0') {
                port_word[port_index] = *str;
                port_index++;
                str++;
            }
            snprintf(port_word, 4, "%d", ip.port);
            goto ret;
        }

        str++;
    }
    ret:
    return ip;
}

ipv4_t addrinfotoipv4(struct addrinfo addrinfo)
{
    LOG_INFO("%s", addrinfo.ai_addr->sa_data);
    return (ipv4_t){0};
}

ipv4_t sockaddrtoipv4(struct sockaddr sockaddr)
{
    LOG_INFO("%s", sockaddr.sa_data);
    return (ipv4_t){0};
}
