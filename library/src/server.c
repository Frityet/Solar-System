//
// Created by Frityet on 2022-01-16.
//

#include "server.h"

#include <stdio.h>
#include <netdb.h>
#include <unistd.h>

#include <logger.h>
#include <signal.h>
#include <arpa/inet.h>

//#define ENUMERATE_ADDRINFO(_name, _addrinfo) for ()

local void sigchild_handler(ATTRIBUTE(unused) int n)
{
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

local void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

struct server create_server(uint16_t port)
{
    struct server server = {
        .connected_clients = create_clientlist(),
        .port = port,
        .connected_client_count = 0
    };

    char portstr[5] = {0};
    snprintf(portstr, 4, "%hu", port);

    struct addrinfo hint = {0}, *addrinfo = NULL;
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE;

    int addrinfo_status = 0;
    if ((addrinfo_status = getaddrinfo("localhost", portstr, &hint, &server.address_info)) != 0) {
        LOG_ERROR("Could not get address info!\nReason: %s", gai_strerror(addrinfo_status));
        return EMPTY(struct server);
    }

    int yes = 1;
    for (struct addrinfo *node = server.address_info; addrinfo != NULL; addrinfo = addrinfo->ai_next) {
        server.socket = socket(node->ai_family, node->ai_socktype, node->ai_protocol);
        if (server.socket == -1) {
            LOG_WARNING("Could not bind socket!\nReason: %s", strerror(errno));
            continue;
        }

        if (setsockopt(server.socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            LOG_FATAL("Could not set socket option!\nReason: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }

        if (bind(server.socket, node->ai_addr, node->ai_addrlen) == -1) {
            LOG_FATAL("Could not bind port!\nReason: %s", strerror(errno));
            close(server.socket);
            continue;
        }

        break;
    }

    struct sigaction sig = {0};
    sig.sa_handler = sigchild_handler;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = SA_RESTART;

    if (sigaction(SIGCHLD, &sig, NULL) == -1) {
        LOG_FATAL("Could not execute sigaction!\nReason: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    return server;
}



struct client *wait_for_connection(struct server *server)
{
    struct sockaddr client_address;
    socklen_t clientaddr_size = sizeof(client_address);
    char buffer[INET_ADDRSTRLEN];
    filedescriptor_t socket;

    puts("Waiting for connection...");
    while (true) {
        socket = accept(server->socket, &client_address, &clientaddr_size);
        if (socket == -1) {
            LOG_DEBUG("No connection!\nError: %s", strerror(errno));
            continue;
        }
        break;
    }

    inet_ntop(client_address.sa_family, get_in_addr(&client_address), buffer, sizeof(buffer));
    LOG_DEBUG("%s connected", buffer);

    if (send(socket, "Ping", 5, 0) == -1) {
        LOG_ERROR("Could not send ping message!\nReason: %s", strerror(errno));
    }

    return add_client(&server->connected_clients, socket);
}

void free_server(struct server *server)
{
    free_clientlist(&server->connected_clients);
    close(server->socket);
    freeaddrinfo(server->address_info);
}
