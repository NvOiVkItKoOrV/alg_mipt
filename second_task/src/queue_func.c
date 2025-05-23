#include "queue_func.h"

queue_t* queue_ctor()
{
    queue_t* queue = (queue_t*)calloc(1, sizeof(queue_t));
    queue->capacity = QUEUE_CAPACITY;
    queue->tail     = 0;
    queue->head     = 0;
    queue->jump_id = 0;
    queue->data = (char**)calloc(queue->capacity, sizeof(char*));
    queue_push(queue, "homepage");
    return queue;
}


void queue_dtor(queue_t* queue)
{
    for (int counter = queue->head;
             counter <= queue->tail;
             counter++)
        free(queue->data[counter]);

    
    queue->capacity = -1;
    queue->tail     = -1;
    queue->head     = -1;
    queue->jump_id  = -1;
    free(queue->data);
    free(queue);
}


char* queue_pop(queue_t* queue)
{
    assert(queue->tail != queue->head);

    char* pop_elem = (char*)calloc(MAX_URL_LENGTH, sizeof(char));
    strcpy(pop_elem, queue->data[queue->head]);

    memset(queue->data[queue->head], '\0', MAX_URL_LENGTH);
    queue->head++;

    return pop_elem;
}


void queue_push(queue_t* queue, const char* push_elem)
{
    assert(queue->tail != queue->capacity);
    queue->data[queue->tail] = (char*)calloc(MAX_URL_LENGTH, sizeof(char));

    strcpy(queue->data[queue->tail], push_elem);
    queue->tail++;
}