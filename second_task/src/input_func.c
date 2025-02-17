#include "browser_history.h"

void user_interface()
{
    bool is_browsing = true;
    size_t jump_counter = 0;
    queue_t* history = queue_ctor();
    queue_t* url = queue_ctor();

    while(is_browsing)
    {  
        proc_buf_val(&jump_counter, &is_browsing, history, url);
    }
    print_browser_history2stdin(history);
    queue_dtor(history);
    queue_dtor(url);
}


void proc_buf_val(size_t* jump_counter, bool* is_browsing,  queue_t* history, queue_t* url)
{
    size_t str_len = 0; 
    char* buf = NULL;
    getline(&buf, &str_len, stdin); 

    str_len = strlen(buf);

    char* command = (char*)calloc(21, sizeof(char));
    char* command_parameter = (char*)calloc(21, sizeof(char));
    assert(command);
    assert(command_parameter);
    sscanf(buf,"%s %s\n",command, command_parameter);
    free(buf);

    make_browser_action(command, command_parameter, jump_counter, history, url, is_browsing);

    free(command);
    free(command_parameter);
}


void make_browser_action(const char* command, const char* command_parameter, size_t* jump_counter, queue_t* history, queue_t* url, bool* is_browsing)
{    
    if(!strcmp(command, "visit"))
    {
        //CHECK COMMAND PARAMETER
        queue_push(url, command_parameter);
        queue_push(history, command_parameter);
    }
    else if (!strcmp(command, "back") && *jump_counter < MAX_JUMPS_VAL)
    {
        (*jump_counter)++;
        int jump_val = make_a_num(command_parameter);
        jump_func(BACK, jump_val, history, url);        
    }
    else if (!strcmp(command, "forward") && *jump_counter < MAX_JUMPS_VAL)
    {
        (*jump_counter)++;
        int jump_val = make_a_num(command_parameter);
        jump_func(FORWARD, jump_val, history, url);
    }
    else
        *is_browsing = false;
}

//TODO: check indexes of data!!!
void jump_func(side2jump_t side2jump, const int jump_val,  queue_t* history, queue_t* url)
{
    switch(side2jump)
    {
    case BACK:
        url->jump_id = url->tail - jump_val - 1;
        if (url->jump_id < 0)
        {
            url->jump_id = 0;
            queue_push(history, url->data[url->jump_id]);
        }
        else    
        {
            queue_push(history, url->data[url->jump_id]);
        }
        break;
    case FORWARD:
        url->jump_id += jump_val;
        if (url->jump_id > url->tail - 1)
        {
            url->jump_id = url->tail - 1;
            queue_push(history, url->data[url->jump_id]);
        }
        else 
        {
            queue_push(history, url->data[url->jump_id]);
        }
        break;
    default: 
        printf("Jump error!!!\n");
        break;
    }
}


int make_a_num(const char* str)
{
    char* endptr = NULL;
    int num_val = (size_t)strtod(str, &endptr);

    if (endptr == NULL)
    {
        printf("Invalid jump argument!\n");
        exit(0);
    }
    return num_val;
}


void  print_browser_history2stdin(queue_t* history)
{   
    printf("===========================================\n");
    printf("NOW BROWSER HISTORY:\n");
    for (int counter = history->head; counter < history->tail; counter++)
        printf("%s\n", history->data[counter]);

    printf("===========================================\n");
}