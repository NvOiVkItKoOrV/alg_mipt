#include "browser_history.h"

void user_interface()
{
    bool is_browsing = true;
    size_t jump_counter = 0;
    queue_t* history = queue_ctor();

    while(is_browsing)
    {  
        proc_buf_val(&jump_counter, &is_browsing, history);
    }
    print_browser_history2stdin(history);
    queue_dtor(history);
}


void proc_buf_val(size_t* jump_counter, bool* is_browsing,  queue_t* history)
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

    make_browser_action(command, command_parameter, jump_counter, history, is_browsing);

    free(command);
    free(command_parameter);
}


void make_browser_action(const char* command, const char* command_parameter, size_t* jump_counter, queue_t* history, bool* is_browsing)
{    
    if(!strcmp(command, "visit"))
    {
        //CHECK COMMAND PARAMETER
        queue_push(history, command_parameter);
        history->jump_id = history->tail - 1;
    }
    else if (!strcmp(command, "back") && *jump_counter < MAX_JUMPS_VAL)
    {
        (*jump_counter)++;
        int jump_val = make_a_num(command_parameter);
        jump_func(BACK, jump_val, history);        
    }
    else if (!strcmp(command, "forward") && *jump_counter < MAX_JUMPS_VAL)
    {
        (*jump_counter)++;
        int jump_val = make_a_num(command_parameter);
        jump_func(FORWARD, jump_val, history);
    }
    else
        *is_browsing = false;
}


void jump_func(side2jump_t side2jump, const int jump_val,  queue_t* history)
{
    switch(side2jump)
    {
    case BACK:
        history->jump_id = history->jump_id - jump_val;
        if (history->jump_id < 0)
        {
            history->jump_id = 0;
            queue_push(history, history->data[history->jump_id]);
        }
        else    
        {
            queue_push(history, history->data[history->jump_id]);
        }
        break;
    case FORWARD:
        history->jump_id += jump_val;
        if (history->jump_id > history->tail - 1)
        {
            history->jump_id = history->tail - 1;
            queue_push(history, history->data[history->jump_id]);
        }
        else 
        {
            queue_push(history, history->data[history->jump_id]);
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