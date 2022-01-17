#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include <server.h>

#include <jobs.h>


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;


    pthread_exit(NULL);
}
