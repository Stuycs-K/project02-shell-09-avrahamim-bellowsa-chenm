#ifndef SHELL_H
#define SHELL_H

#define BUFFER_SIZE 256
#define TOKEN_SIZE 256

int special_cmd(char ** arg_ary); //is the cmd a shell specific cmd?
void sighandler(int signo); //handle the signal

#endif
