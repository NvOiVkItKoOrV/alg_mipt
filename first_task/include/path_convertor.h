#ifndef PATH_CONVERTOR_H
#define PATH_CONVERTOR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


#define PATH_MAX_LENGTH 4096
#define MAX_DIRECTORY_LENGTH 100

#define QUEUE_CAPACITY 10



typedef struct queue
{
    char** dir_names_data;
    int tail;
    int capacity;
    int head;
} queue;

queue* queue_ctor();
void queue_dtor(queue* queue);
char* queue_pop(queue* queue);
void queue_push(queue* queue, char* push_elem);

void extra_slashes_deleter(const char* str, char* path);
int skip_extra_slashes(const char* str, int counter);
queue* make_dir_names_data(char* str);
void add_dir_name2data(queue* dir_data, char* str, int* str_symb_counter);
char* make_final_path(queue* queue);
void path_dots_deleter(queue* queue);


#endif /* PATH_CONVERTOR_H */