#ifndef PATH_CONVERTOR_H
#define PATH_CONVERTOR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


#define PATH_MAX_LENGTH 4096
#define MAX_DIRECTORY_LENGTH 100

#define QUEUE_CAPACITY 100



typedef struct queue_t
{
    char** dir_names_data;
    int tail;
    int capacity;
    int head;
} queue_t;

queue_t* queue_ctor();
void queue_dtor(queue_t* queue);
char* queue_pop(queue_t* queue);
void queue_push(queue_t* queue, char* push_elem);

void extra_slashes_deleter(const char* str, char* path);
int skip_extra_slashes(const char* str, int counter);
queue_t* make_dir_names_data(char* str);
void add_dir_name2data(queue_t* dir_data, char* str, int* str_symb_counter);
char* make_final_path(queue_t* queue);
void path_dots_deleter(queue_t* queue);


#endif /* PATH_CONVERTOR_H */