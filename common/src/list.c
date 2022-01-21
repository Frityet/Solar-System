//
// Created by Frityet on 2022-01-17.
//

#include "list.h"

#include <utilities.h>


void *create_list(size_t type_size, size_t count)
{
    count = round_to_2nd_power(count);
    struct list_data *list   = memset(alloc_or_kablooey(sizeof(*list) + type_size * count, __LINE__, __FILE__), 0, sizeof(*list));
    list->used_spaces   = 0;
    list->total_spaces  = count;
    list->type_size     = type_size;
    list->total_size    = type_size * count;
    list->array         = list + 1;
    return list->array;
}

void grow_list(void *ptr)
{
    struct list_data *list = listinfo(ptr);
    size_t new_size = list->type_size * (list->total_spaces *= 2);
    list->total_size = new_size;
    void *new_alloc = realloc(list, sizeof(struct list_data) + new_size);
    if (new_alloc == NULL)
        return;
    free(list);
    list = new_alloc;
    list->array = list + 1;
}

void *remove_item(void *ptr, size_t index)
{
    struct list_data *info = listinfo(ptr);
    uint8_t *newlist = create_list(info->type_size, info->total_spaces - 1),
            *list_array = info->array;

    for (size_t i = 0; i < info->used_spaces; ++i) {
        newlist[i] = list_array[i];
    }

    return newlist;
}
