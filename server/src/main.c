#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include <server.h>

#include "jobs.h"

#define local static

local pthread_t network_thread;

//TODO: shitty name
local void *networking_thread(void *arg)
{
    (void)arg;
    puts("Started networking thread");

    struct server server = server_initialise(32768);

    if (server.socket == 0) {
        fputs("Server initialisation failed!", stderr);
        pthread_exit(NULL);
    }

    while (server_accept_client(&server)) {
        puts("Client connected!");

        int input = getchar();
        if (input == 'q')
            break;
    }

    close(server.socket);

    return NULL;
}

local void cmd_interpreter(void)
{

}

__attribute__((unused)) local void func1(struct job_args *args)
{
    printf("Thread 1: argc: %zu\n", args->argc);
}

__attribute__((unused)) local void func2(struct job_args *args)
{
    printf("Thread 2: argc: %zu\n", args->argc);
}

__attribute__((unused)) local void func3(struct job_args *args)
{
    printf("Thread 3: argc: %zu\n", args->argc);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    (void)networking_thread;
    (void)cmd_interpreter;
    (void)network_thread;

    int *array = malloc(3);

    for (int i = 0; i < 0xFF; ++i) {
        printf("address: %p, value: %c\n", (void *)&array[i], array[i]);
    }

//    int i = 0, j = 0, k = 0;
//
//    struct worker *worker = employ_worker(func1, JOB_ARGS(&i, &j, &k), NULL, NULL);
//    add_job(worker, func2, JOB_ARGS("Hello ", "World!"), NULL);
//    add_job(worker, func3, JOB_ARGS("Test", "argument!", &i, &j, &k), NULL);
//    run_worker(worker);
//    puts("Worker running");
//    layoff_worker(worker);
//
//    pthread_exit(NULL);
}
