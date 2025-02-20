#include "path_convertor.h"

list_info_t* list_ctor()
{
    list_info_t* lst_info = (list_info_t*)calloc(1, sizeof(list_info_t));
    lst_info->head = NULL;
    lst_info->tail = NULL;

    return lst_info;
}


void list_dtor(list_info_t* lst_info)
{
    for (list_t* cmp = lst_info->head; cmp != lst_info->tail;)
    {
        free(cmp->dir_name);
        list_t* lst2free = cmp;
        cmp = cmp->next;
        free(lst2free);
    }
    free((lst_info->tail)->dir_name);
    free(lst_info->tail);
    free(lst_info);
}


char* list_pop(list_t** lst)
{

    char* pop_elem = (char*)calloc(LIST_CAPACITY, sizeof(char));
    strcpy(pop_elem, (*lst)->dir_name);
    free((*lst)->dir_name);

    (*lst)->prev->next = (*lst)->next;
    (*lst)->next->prev = (*lst)->prev;
    list_t* lst2rm = *lst;
    (*lst) = (*lst)->prev;
    free(lst2rm);
    return pop_elem;
}


void list_push(list_info_t* lst_info, char* push_elem)
{
    if (lst_info->head == NULL)
    {
        lst_info->head = (list_t*)calloc(1, sizeof(list_t));
        lst_info->tail = lst_info->head;
        lst_info->head->dir_name = (char*)calloc(LIST_CAPACITY, sizeof(char));
        strcpy((lst_info->head)->dir_name, push_elem);
        return;
    }

    list_t* new_tail = (list_t*)calloc(1, sizeof(list_t));

    new_tail->prev = lst_info->tail;
    (lst_info->tail)->next = new_tail;
    lst_info->tail = new_tail;
    (lst_info->tail)->dir_name = (char*)calloc(LIST_CAPACITY, sizeof(char));
    strcpy((lst_info->tail)->dir_name, push_elem);
}