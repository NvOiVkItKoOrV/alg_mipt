#ifndef QUEUE_FUNC_H
#define QUEUE_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define QUEUE_CAPACITY 100
#define MAX_URL_LENGTH 21

typedef struct queue_t
{
    char** data;
    int jump_id;
    int head;
    int tail;
    int capacity;

} queue_t;

queue_t* queue_ctor();
void queue_dtor(queue_t* queue);

char* queue_pop(queue_t* queue);
void queue_push(queue_t* queue, const char* push_elem);

#endif /* QUEUE_FUNC_H */