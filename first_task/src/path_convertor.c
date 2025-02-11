#include "../include/path_convertor.h"


void extra_slashes_deleter(const char* str, char* path)
{
    int str_counter = 0;
    int path_counter = 0;
    while (str_counter < PATH_MAX_LENGTH && str[str_counter] != '\0')
    {
        switch (str[str_counter])
        {
            case '\\':
                str_counter = skip_extra_slashes(str, str_counter + 1);
                break;
            default:
                path[path_counter++] = str[str_counter++];
                break;
        }
    }
}


int skip_extra_slashes(const char* str, int counter)
{
    while(str[counter] == '\\')
    {
        counter++;
    }
    return counter;
}


queue* make_dir_names_data(char* str)
{   
    int data_symb_counter = 0;

    queue* dir_data = queue_ctor();

    while (str[data_symb_counter] != '\0'     &&
           data_symb_counter < PATH_MAX_LENGTH)
    {
        switch (str[data_symb_counter])
        {
        case '\\':
            data_symb_counter++;
            add_dir_name2data(dir_data, str, &data_symb_counter);
            break;
        
        default:
            break;
        }
    }
    free(str);
    return dir_data;
}


void add_dir_name2data(queue* dir_data, char* str, int* str_symb_counter)
{
    int buf_rec_size = 0;
    char* buf4copying_dir = calloc(MAX_DIRECTORY_LENGTH, sizeof(char));

    for (; str[*str_symb_counter] != '\\' &&
           str[*str_symb_counter] != '\0' &&
           buf_rec_size < MAX_DIRECTORY_LENGTH;)
        buf4copying_dir[buf_rec_size++] = str[(*str_symb_counter)++];

    queue_push(dir_data, buf4copying_dir);
    free(buf4copying_dir);
}


char* make_final_path(queue* queue)
{
    char* buf = calloc(PATH_MAX_LENGTH, sizeof(char));
    int buf_counter = 0;
    for (int counter = queue->head; counter < queue->tail; counter++)
    {
        memset(buf + buf_counter, '\\', 1);
        buf_counter++;
        if(*(queue->dir_names_data[counter]) != '\0')
        {
            strcpy(buf + buf_counter, queue->dir_names_data[counter]);
            buf_counter = buf_counter + strlen(queue->dir_names_data[counter]);
        }
    }
    return buf;
}


void path_dots_deleter(queue* queue)
{
    int double_dots_counter = 0;
    const char double_dots[] = "..";
    const char dot[] = ".";
    for (int counter = queue->tail;
         queue->tail > queue->head; 
                            counter--)
    {
        if(!strcmp(queue->dir_names_data[counter], double_dots))
        {
            queue->dir_names_data[counter] = '\0';
            double_dots_counter++;
        }
        else if(!strcmp(queue->dir_names_data[queue->tail], dot))
        {
            queue->dir_names_data[queue->tail] = '\0';
        }
        else
        {   
            if (double_dots_counter)
                queue->dir_names_data[counter] = '\0';

        }

    }

    if (!double_dots_counter)
    {
        printf("Going upper than the root directory is not possible.\n");
        free(queue->dir_names_data);
        free(queue);
        exit(0);
    }
}