#ifndef BROWSER_HISTORY_H
#define BROWSER_HISTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "queue_func.h"

#define MAX_URL_LENGTH 21
#define MAX_JUMPS_VAL 100


typedef enum
{
    BACK = 0,
    FORWARD = 1
} side2jump_t;

void user_interface();
void proc_buf_val(size_t* jump_counter, bool* is_browsing,  queue_t* history);
void make_browser_action(const char* command, const char* command_parameter, size_t*    jump_counter, 
                         queue_t*    history, bool*       is_browsing);
void print_browser_history2stdin(queue_t* history);
void jump_func(side2jump_t side2jump, const int jump_val,  queue_t* history);
int make_a_num(const char* str);

#endif /* BROWSER_HISTORY_H */