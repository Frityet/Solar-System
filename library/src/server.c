//
// Created by Frityet on 2021-12-31.
//

#include "server.h"
#include "client.h"

#include <errno.h>
extern int errno;
#include <string.h>
#include <stdlib.h>

#include <logger.h>
#include <utilities.h>

#include <lua.h>


struct server server_initialise(uint16_t portnumber)
{
    struct server server = {0};

    char port[4] = {0};
    snprintf(port, 4, "%d", portnumber);

    struct addrinfo hint = {0};
    hint.ai_family =    AF_INET;
    hint.ai_socktype =  SOCK_STREAM;
    hint.ai_flags =     AI_PASSIVE;

    int addrinfo_res = getaddrinfo(NULL, port, &hint, &(server.server_info));
    if (addrinfo_res != 0) {
        LOG_ERROR("Could not start server!\nError: %s", gai_strerror(addrinfo_res));
        return (struct server){0};
    }

    server.socket = socket(server.server_info->ai_family, server.server_info->ai_socktype, server.server_info->ai_protocol);
    if (server.socket == -1) {
        LOG_ERROR("Could not create socket!\nError: %s", strerror(errno));
        return (struct server){0};
    }

    if (bind(server.socket, server.server_info->ai_addr, server.server_info->ai_addrlen) == -1) {
        LOG_ERROR("Could not bind socket!\nError: %s", strerror(errno));
        return (struct server){0};
    }

    if (listen(server.socket, SERVER_MAX_QUEUE) != 0) {
        LOG_ERROR("Could not listen on socket!\nError: %s", strerror(errno));
        return (struct server){0};
    }

    return server;
}

filedescriptor_t server_accept_client(struct server *server)
{
    struct sockaddr client_addr;
    uint32_t len = sizeof(client_addr);
    LOG_INFO("Waiting for connection!");
    filedescriptor_t sock = accept(server->socket, &client_addr, &len);
    LOG_INFO("Connection found!");
    if (sock == -1) {
        LOG_ERROR("Could not accept client!\nReason: %s", strerror(errno));
        return 0;
    }

    add_client(&(server->connected_players), sockaddrtoipv4(client_addr), sock);

    return sock;
}
