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
    char* buf = (char*)calloc(PATH_MAX_LENGTH, sizeof(char));
    int buf_counter = 0;
    for (list_t* counter = lst_info->head; counter < lst_info->tail; counter = counter->next)
    {
        if(*(counter->dir_name) != '\0')
        {
            memset(buf + buf_counter, '/', 1);
            buf_counter++;
            strcpy(buf + buf_counter, counter->dir_name);
            buf_counter = buf_counter + strlen(counter->dir_name);
        }
    }
    
    path_dots_deleter(lst_info);
    list_dtor(lst_info);
    return buf;
}


void path_dots_deleter(list_info_t* lst_info)
{
    for(list_t* cmp = lst_info->head; cmp != lst_info->tail; cmp = cmp->next)
        printf("%s\n", cmp->dir_name);
        printf("%s\n", lst_info->tail);
    int double_dots_counter = 0;
    const char double_dots[] = "..";
    const char dot[] = ".";
    for (list_t* counter = lst_info->tail;
             counter != lst_info->head; 
             counter = counter->prev)
    {
        if(!strcmp(counter->dir_name, double_dots))
        {
            char* str2delete = list_pop(lst_info);
            free(str2delete);
            double_dots_counter++;
        }
        else if(!strcmp(counter->dir_name, dot))
        {
            char* str2delete = list_pop(lst_info);
            free(str2delete);
        }
        else
        {   
            if (double_dots_counter)
            {
                char* str2delete = list_pop(lst_info);
                free(str2delete);
                double_dots_counter--;
            }
        }

    }

    if (double_dots_counter != 0)
    {
        printf("Going upper than the root directory is not possible.\n");
        exit(0);
    }
}