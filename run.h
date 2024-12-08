#ifndef RUN_H
#define RUN_H

void flow_execution(char ** chunks, int index, int size, struct sigaction old); 

int run_cmd(char * cmd_block,struct sigaction old);

#endif