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
   int file_desc = open("tricky.txt",O_WRONLY | O_APPEND); 
      
    // here the newfd is the file descriptor of stdout (i.e. 1) 
    dup2(file_desc, 1) ;  
          
    // All the printf statements will be written in the file 
    // "tricky.txt" 
    printf("I will be printed in the file tricky.txt\n"); 
}

int redirect_stdout_create_file(char * name){
    int fd = open(name, O_CREAT | O_TRUNC | O_WRONLY );
    return redirect_stdout(fd);
}

int redirect_stdin(int fd){
    int stdfileno = fileno(stdin);
    int old_stdin = dup(stdfileno);
    dup2(fd, stdfileno);
    return old_stdin;
}

int redirect_stdin_create_file(char * name){
    int fd = open(name, O_CREAT | O_TRUNC | O_WRONLY);
    return redirect_stdin(fd);
}


void reset_fds(int old_stdin, int old_stdout){
    int stdinno = fileno(stdin);
    int stdoutno = fileno(stdout);

    dup2(old_stdin, stdinno);
    dup2(old_stdout, stdoutno);
}