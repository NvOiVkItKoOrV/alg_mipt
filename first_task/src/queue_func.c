#include "../include/path_convertor.h"

queue_t* queue_ctor()
{
    queue_t* queue = (queue_t*)calloc(1, sizeof(queue_t));
    queue->capacity = QUEUE_CAPACITY;
    queue->tail     = 0;
    queue->head     = 0;
    queue->dir_names_data = (char**)calloc(queue->capacity, sizeof(char*));
    return queue;
}


void queue_dtor(queue_t* queue)
{
    for (int counter = queue->head;
             counter <= queue->tail;
             counter++)
        free(queue->dir_names_data[counter]);

    
    queue->capacity = -1;
    queue->tail     = -1;
    queue->head     = -1;
    free(queue->dir_names_data);
    free(queue);
}


char* queue_pop(queue_t* queue)
{
    assert(queue->tail != queue->head);

    char* pop_elem = (char*)calloc(MAX_DIRECTORY_LENGTH, sizeof(char));
    strcpy(pop_elem, queue->dir_names_data[queue->head]);

    memset(queue->dir_names_data[queue->head], '\0', MAX_DIRECTORY_LENGTH);
    queue->head++;

    return pop_elem;
}


void queue_push(queue_t* queue, char* push_elem)
{
    assert(queue->tail != queue->capacity);
    queue->dir_names_data[queue->tail] = (char*)calloc(MAX_DIRECTORY_LENGTH, sizeof(char));
   
    strcpy(queue->dir_names_data[queue->tail], push_elem);
    queue->tail++;
}