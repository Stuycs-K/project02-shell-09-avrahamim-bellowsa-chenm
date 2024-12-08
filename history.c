#include <string.h>
#include "history.h"
#include <stdlib.h>
struct history_log * new_history_log(char * data){
    struct history_log * new = calloc(sizeof(struct history_log), 1);
    new -> next = NULL;
    strcpy(new->line, data);
    return new;  
}

struct history_log * history_log_add(struct history_log * root, struct history_log * item){
    item->next = root;
    return item;
}
