#ifndef PATH_CONVERTOR_H
#define PATH_CONVERTOR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


#define PATH_MAX_LENGTH 4096
#define MAX_DIRECTORY_LENGTH 100

#define LIST_CAPACITY 4096


typedef struct list_t
{
    char* dir_name;
    list_t* next;
    list_t* prev;
} list_t;


typedef struct list_info_t
{
    list_t* head;
    list_t* tail;
    
} list_info_t;


list_info_t* list_ctor();
void list_dtor(list_info_t* lst_info);
char* list_pop(list_t* lst);
void list_push(list_info_t* lst_info, char* push_elem);

void extra_slashes_deleter(const char* str, char* path);
int skip_extra_slashes(const char* str, int counter);
list_info_t* make_dir_names_data(char* str);
void add_dir_name2data(list_info_t* dir_data, char* str, int* str_symb_counter);
char* make_final_path(list_info_t* queue);
void path_dots_deleter(list_info_t* queue);


#endif /* PATH_CONVERTOR_H */