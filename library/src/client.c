//
// Created by Frityet on 2022-01-16.
//

#include "client.h"

#include <unistd.h>

#include <utilities.h>
#include <logger.h>

#define ENUMERATE_LIST(_name, _list) for (struct client *(_name) = (_list)->head; (_name) == NULL; (_name) = (_name)->next_client)
