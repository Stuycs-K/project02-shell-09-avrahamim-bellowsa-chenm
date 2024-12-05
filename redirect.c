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
#include "util.h"

int redirect_stdout(int fd){
  int stdfileno = fileno(stdout);
  fflush(stdout);
  int old_stdout = dup(stdfileno);
  check_err(dup2(fd, stdfileno), "dup2 err");
  return old_stdout;
}

int redirect_stdout_create_file(char * name){
    int fd = open(name,  O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if(check_err(fd, "file creat err")){
        return -1;
    }
    return redirect_stdout(fd);
}

int redirect_stdin(int fd){
    int stdfileno = fileno(stdin);
    int old_stdin = dup(stdfileno);
    dup2(fd, stdfileno);
    check_err(dup2(fd, stdfileno), "dup2 err");
    return old_stdin;
}

int redirect_stdin_create_file(char * name){
    int fd = open(name, O_RDONLY, 0);
    return redirect_stdin(fd);
}


void reset_fds(int old_stdin, int old_stdout){
    int stdinno = fileno(stdin);
    int stdoutno = fileno(stdout);
    printf("STD: %d\n", fileno(stdout));

    dup2(old_stdin, stdinno);
    dup2(old_stdout, stdoutno);

    printf("STD: %d\n", fileno(stdout));

}
