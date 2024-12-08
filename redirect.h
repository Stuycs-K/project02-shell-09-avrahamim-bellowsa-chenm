#ifndef REDIRECT_H
#define REDIRECT_H

int redirect_stdout(int fd); //redirect stdout to fd
int redirect_stdout_create_file(char * name); //open file and then redirect stdout to it

int redirect_stdin(int fd); //redirect stdin to fd
int redirect_stdin_create_file(char * name); //open file and then redirect stdin to it

void reset_stdin(int old_stdin); //reset stdin to old_stdin
void reset_stdout(int old_stdout); //reset stdout to old_stdout

#endif
