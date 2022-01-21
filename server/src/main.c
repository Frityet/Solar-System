#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include <server.h>

#include <jobs.h>
#include <generic_list.h>

//#define ENUMERATE_LIST(_name, _list) for (struct client *(_name) = (_list)->head; (_name) == NULL; (_name) = (_name)->next_client)


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

//    int64_t *list = create_list(sizeof(int64_t), 3);

    srand(time(NULL));

    LIST(int) list = NEW_LIST(int);

    ADD_ITEM(list, 5);
    ADD_ITEM(list, 10);

    free_list(list);
}
