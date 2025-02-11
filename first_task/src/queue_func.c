#include "../include/path_convertor.h"

queue* queue_ctor()
{
    queue* queue = calloc(1, sizeof(queue));
    queue->capacity = QUEUE_CAPACITY;
    queue->tail     = 0;
    queue->head     = 0;
    queue->dir_names_data = calloc(QUEUE_CAPACITY * MAX_DIRECTORY_LENGTH, sizeof(char));
    return queue;
}


void queue_dtor(queue* queue)
{
    queue->capacity = -1;
    queue->tail     = -1;
    queue->head     = -1;
    
    free(queue->dir_names_data);
    free(queue);
}


char* queue_pop(queue* queue)
{
    assert(queue->tail != queue->head);

    char* pop_elem = calloc(MAX_DIRECTORY_LENGTH, sizeof(char));
    strcpy(pop_elem, queue->dir_names_data[queue->head]);

    memset(queue->dir_names_data[queue->head], '\0', MAX_DIRECTORY_LENGTH);
    queue->head++;

    return pop_elem;
}


void queue_push(queue* queue, char* push_elem)
{
    assert(queue->tail != queue->capacity);

    strcpy(queue->dir_names_data[queue->tail], push_elem);
    queue->tail++;
}