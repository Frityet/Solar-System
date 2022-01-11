#include <stdio.h>

#include <utilities.h>
#define UNIGS_DEBUG
#include <logger.h>

int main()
{
    puts("Started client");
    puts("Connecting to server at localhost:8123");

    struct {
        filedescriptor_t    socket;
        struct addrinfo     *address_info;
    } client;

    struct addrinfo hint = {0};
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    int addrinfo_res = getaddrinfo("localhost", "32768", &hint, &client.address_info);
    if (addrinfo_res != 0) {
        LOG_FATAL("Could not get address info!\nReason: %s", gai_strerror(addrinfo_res));
        return addrinfo_res;
    }

    client.socket = socket(client.address_info->ai_family, client.address_info->ai_socktype, client.address_info->ai_protocol);
    if (client.socket == -1) {
        LOG_FATAL("Could not bind socket!\nReason: %s", strerror(errno));
        return errno;
    }

    int connect_res = connect(client.socket, client.address_info->ai_addr, client.address_info->ai_addrlen);
    if (connect_res == -1) {
        LOG_FATAL("Could not connect!\nReason: %s", strerror(errno));
        return errno;
    }

    LOG_INFO("Successfully connected!");

    return 0;
}
