#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <pwd.h>

#include "colors.h"

int setvalue = 0;
char * home;

//print the prompt
void prompt_print(){
  //dynamically stores cwd in string
  char *cwd = getcwd(NULL, 0);
  if (cwd == NULL){
    perror("getcwd error");
  }

  char * newCWD;
  char tilda[256];
  tilda[0] = '~';
  tilda[1] = '\0';
  if (!setvalue) {setvalue = 1; home = getenv("HOME");}
  if ((newCWD = strstr(cwd, home))) {
      newCWD += strlen(home);
      strcat(tilda, newCWD);
      strcpy(cwd, tilda);
//	fprintf(stderr, "copied\n");
  }
  

  //get username with struct passwd
  uid_t usr = geteuid();
  struct passwd * pas = getpwuid(usr);


  //printf("\n");
  // char prompt[1000];
  // sprintf(prompt,GREEN"%s"COLOREND":"BLUE"%s"COLOREND"$ ", pas->pw_name, cwd );
  // fputs(prompt, stderr);
  printf(GREEN"%s"COLOREND":"BLUE"%s"COLOREND"$ ", pas->pw_name, cwd);
  fflush(stdout);

  free(cwd);
}
