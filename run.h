#ifndef RUN_H
#define RUN_H

//take a parsed cmd chunk and ecexute the required files making the changes to stdin and stdout
void flow_execution(char ** chunks, int index, int size, struct sigaction old); 

//run a cmd_block including reset signal handling
int run_cmd(char * cmd_block,struct sigaction old);

#endif