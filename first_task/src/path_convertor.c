#include "path_convertor.h"

void extra_slashes_deleter(const char* str, char* path)
{
    int str_counter = 0;
    int path_counter = 0;
    while (str_counter < PATH_MAX_LENGTH && str[str_counter] != '\0')
    {
        switch (str[str_counter])
        {
            case '/':
                path[path_counter++] = str[str_counter++];
                str_counter = skip_extra_slashes(str, str_counter);
                break;

            default:
                path[path_counter++] = str[str_counter++];
                break;
        }
    }
}


int skip_extra_slashes(const char* str, int counter)
{
    while(str[counter] == '/')
    {
            counter++;
    }
    return counter;
}


list_info_t* make_dir_names_data(char* str)
{   
    assert(*str == '/');
    int data_symb_counter = 0;

    list_info_t* lst_info = list_ctor();

    while (str[data_symb_counter] != '\0')
    {
        switch (str[data_symb_counter])
        {
        case '/':
            data_symb_counter++;
            add_dir_name2data(lst_info, str, &data_symb_counter);
            break;
        
        default:
            break;
        }
    }
    free(str);
    return lst_info;
}


void add_dir_name2data(list_info_t* lst_info, char* str, int* str_symb_counter)
{
    int buf_rec_size = 0;
    char* buf4copying_dir = (char*)calloc(MAX_DIRECTORY_LENGTH, sizeof(char));
    
    for (; str[*str_symb_counter] != '/' &&
           str[*str_symb_counter] != '\0';
           buf_rec_size++, (*str_symb_counter)++)
    {   
        buf4copying_dir[buf_rec_size] = str[(*str_symb_counter)];
    }
    list_push(lst_info, buf4copying_dir);
    free(buf4copying_dir);
}


char* make_final_path(list_info_t* lst_info)
{
    path_dots_deleter(lst_info); 

    char* buf = (char*)calloc(PATH_MAX_LENGTH, sizeof(char));
    int buf_counter = 0;
    
    for (list_t* counter = lst_info->head; counter != lst_info->tail; counter = counter->next)
    {
        buf[buf_counter] = '/';
        buf_counter++;
        strcpy(buf + buf_counter, counter->dir_name);
        buf_counter += strlen(counter->dir_name);
    }
    buf[buf_counter++] = '/';
    strcpy(buf + buf_counter, lst_info->tail->dir_name);

    list_dtor(lst_info);
    return buf;
}


void path_dots_deleter(list_info_t* lst_info)
{


    int double_dots_counter = 0;
    const char double_dots[] = "..";
    const char dot[] = ".";
    list_t* counter = lst_info->tail;

    if (!strcmp((lst_info->head)->dir_name, double_dots))
    {
        printf("Wrong path");
        exit(0);
    }
    else if (!strcmp((lst_info->head)->dir_name, dot))
    {
        list_t* list2rm = lst_info->head;
        lst_info->head = (lst_info->head)->next;
        lst_info->head->prev = NULL;
        free(list2rm->dir_name);
        free(list2rm);
    }

    for (list_t* counter = lst_info->tail;
        counter != lst_info->head;)
    {
        if (counter->prev == NULL)
        exit(0);

        if(!strcmp(counter->dir_name, double_dots))
        {
            char* str2delete = list_pop(&counter);
            free(str2delete);
            double_dots_counter++;
            
        }
        else if(!strcmp(counter->dir_name, dot))
        {
            char* str2delete = list_pop(&counter);
            free(str2delete);
        }
        else
        {   
            if (double_dots_counter)
            {
                char* str2delete = list_pop(&counter);
                free(str2delete);
                double_dots_counter--;
            }
            else
                counter = counter->prev;
        }

    } 

    if (double_dots_counter != 0)
    {
        printf("Going upper than the root directory is not possible.\n");
        exit(0);
    }
}