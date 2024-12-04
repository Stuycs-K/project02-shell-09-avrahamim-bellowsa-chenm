#ifndef REDIRECT_H
#define REDIRECT_H

int redirect_stdout(int fd);
int redirect_stdout_create_file(char * name);

int redirect_stdin(int fd);
int redurect_stdin_create_file(char * name);

void reset_fds(int old_stdin, int old_stdout);

#endif