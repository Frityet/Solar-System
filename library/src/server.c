//
// Created by Frityet on 2021-12-31.
//

#include "server.h"

#include <errno.h>
extern int errno;
#include <string.h>
#include <stdlib.h>

#include <logger.h>
#include <utilities.h>
#include <unistd.h>

#include "client.h"

struct server server_initialise(uint16_t portnumber)
{
    struct server server = {0};

    char port[5] = {0};
    snprintf(port, 5, "%d", portnumber);

    struct addrinfo hint = {0};
    hint.ai_family =    AF_INET;
    hint.ai_socktype =  SOCK_STREAM;
    hint.ai_flags =     AI_PASSIVE;

    int addrinfo_res = getaddrinfo("localhost", port, &hint, &(server.server_info));
    if (addrinfo_res != 0) {
        LOG_ERROR("Could not start server!\n"
                  "Error: %s", gai_strerror(addrinfo_res));
        return EMPTY(struct server);
    }

    struct addrinfo *addr = NULL;
    for (addr = server.server_info; addr != NULL; addr = addr->ai_next) {
        if ((server.socket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol) == -1)) {
            LOG_DEBUG("Address %s: %s", addr->ai_canonname, strerror(errno));
            continue;
        }

        int sockopt_res = 1;
        if (setsockopt(server.socket, SOL_SOCKET, SO_REUSEADDR, &sockopt_res, sizeof(int)) == -1) {
            LOG_ERROR("setsockopt failed!\n"
                      "Reason: %s", strerror(errno));
            return EMPTY(struct server);
        }

        if (bind(server.socket, addr->ai_addr, addr->ai_addrlen) == -1) {
            LOG_DEBUG("Bind failed to addr %s (%s)", addr->ai_canonname, strerror(errno));
            continue;
        }
        break;
    }

    if (addr == NULL) {
        LOG_ERROR("Bind failed!\n"
                  "Reason: %s", strerror(errno));
        return EMPTY(struct server);
    }

    if (listen(server.socket, SERVER_MAX_QUEUE) == -1) {
        LOG_ERROR("Listen failed!\n"
                  "Reason: %s", strerror(errno));
        return EMPTY(struct server);
    }


    struct sigaction action;
    return server;
}

void free_server(struct server *server)
{
    freeaddrinfo(server->server_info);
    free(server);
}

filedescriptor_t server_accept_client(struct server *server)
{
    struct sockaddr *client_addr;
    uint32_t len = sizeof(client_addr);
    LOG_INFO("Waiting for connection!");
    filedescriptor_t sock = accept(server->socket, )
}
