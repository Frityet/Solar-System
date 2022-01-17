#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include <server.h>

#include <jobs.h>

//#define local static

//local pthread_t network_thread;
//
//local void *networking_thread(void *arg)
//{
//    (void)arg;
//    puts("Started networking thread");
//
//    struct server server = server_initialise(32768);
//
//    if (server.socket == 0) {
//        fputs("Server initialisation failed!", stderr);
//        pthread_exit(NULL);
//    }
//
//    while (server_accept_client(&server)) {
//        puts("Client connected!");
//
//        int input = getchar();
//        if (input == 'q')
//            break;
//    }
//
//    close(server.socket);
//
//    return NULL;
//}
//
//local void cmd_interpreter(void)
//{
//
//}

local void func1(struct job_args *args)
{
    printf("Func 1: argc: %zu\n", args->argc);
}

local void func2(struct job_args *args)
{
    printf("Func 2: argc: %zu\n", args->argc);
}

local void func3(struct job_args *args)
{
    printf("Func 3: argc: %zu\n", args->argc);
}

local void func4(struct job_args *args)
{
    printf("Func 4: argc: %zu\n", args->argc);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    int i = 0, j = 0, k = 0;

    struct worker *worker = employ_worker(func1, JOB_ARGS(&i, &j, &k), NULL, NULL);
    add_job(worker, func2, JOB_ARGS("Hello ", "World!"), NULL);
    run_worker(worker);
    sleep(1);
    puts("Worker running");
    add_job(worker, func3, JOB_ARGS("Test", "argument!", &i, &j, &k), NULL);
    add_job(worker, func4, JOB_ARGS("Multithreading", "is", "hard!"), NULL);


    layoff_worker(worker);

    pthread_exit(NULL);
}
