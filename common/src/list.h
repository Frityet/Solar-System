//
// Created by Frityet on 2022-01-17.
//

#ifndef SOLARSYSTEM_COMMON_LIST_
#define SOLARSYSTEM_COMMON_LIST_

#include "solarsystem_types.h"

#include "logger.h"

//#define list(_type) (_type) *

#define NEW_LIST(_type) create_list(sizeof(_type), 2)
#define ADD_ITEM(_list, _item) if (listinfo(_list)->used_spaces == listinfo(_list)->total_spaces) grow_list(_list); (_list)[free_index(_list)] = _item; listinfo(_list)->used_spaces++

struct list_data {
    size_t      type_size, total_size, used_spaces, total_spaces;
    void        *array;
};

static inline struct list_data *listinfo(void *ptr)
{
    struct list_data *list = (struct list_data *)((byte_t *)ptr - sizeof(struct list_data));
    if (list->array != ptr) {
        LOG_ERROR("Could not get info of ptr %p! Are you sure this is a list?", ptr);
    }
    return list;
}

void *create_list(size_t type_size, size_t count);
void grow_list(void *ptr);
void *remove_item(void *ptr, size_t index);

static inline unsigned int free_index(void *list)
{
    return listinfo(list)->used_spaces;
}


static inline size_t list_length(void *ptr)
{
    return listinfo(ptr)->used_spaces;
}

static inline size_t list_max(void *ptr)
{
    return listinfo(ptr)->total_spaces;
}

static inline void free_list(void *ptr)
{
    free(listinfo(ptr));
}

#endif //SOLARSYSTEM_COMMON_LIST_
