#ifndef HISTORY_H
#define HISTORY_H

#define LONGESTLINE 256
struct history_log{
    char line[LONGESTLINE];
    struct history_log * next;
};


struct history_log * new_history_log(char * data); //init a struct 
struct history_log * history_log_add(struct history_log * root, struct history_log * item); // add a struct to a linked list

#endif