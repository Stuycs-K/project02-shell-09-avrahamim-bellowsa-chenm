#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "shell.h"
#include "util.h"

int check_err(int err, char * err_type){
  if(err == -1){
    char err_buff[BUFFER_SIZE];
    sprintf(err_buff, "%s: ", err_type);
    perror(err_buff);
    return -1;
  }
  return 0;
}