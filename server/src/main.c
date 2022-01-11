#include <stdlib.h>
#include <pthread.h>
#include <logger.h>



#include "server.h"

local pthread_t network_thread;

//TODO: shitty name
local void *networking_thread(void *arg)
{
    UNUSED(arg);
    LOG_INFO("Started networking thread");

    struct server server = server_initialise(8193);

    while (server_accept_client(&server)) {
        LOG_INFO("Client connected!");
    }

    return NULL;
}

local void cmd_interpreter(void)
{

}



int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    initalise_logger("tnh3d-server.log");


    pthread_create(&network_thread, NULL, networking_thread, NULL);

    cmd_interpreter();

    pthread_exit(NULL);
}
