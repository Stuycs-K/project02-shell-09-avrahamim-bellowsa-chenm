#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

#include "redirect.h"

int redirect_stdout(int fd){
    int old_stdout = dup(stdout);
    dup2(fd, stdout);
    return old_stdout;
}

int redirect_stdout_create_file(char * name){
    int fd = open(name, O_CREAT | O_TRUNC );
    return redirect_stdout(fd);
}

int redirect_stdin(int fd){
    int old_stdin = dup(stdin);
    dup2(fd, stdin);
    return old_stdin;
}

int redirect_stdout_create_file(char * name){
    int fd = open(name, O_CREAT | O_TRUNC );
    return redirect_stdin(fd);
}


void reset_fds(int old_stdin, int old_stdout){
    dup2(old_stdin, stdin);
    dup2(old_stdout, stdout);
}