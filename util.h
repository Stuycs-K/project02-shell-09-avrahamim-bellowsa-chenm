#ifndef UTIL_H
#define UTIL_H

int check_err(int err, char * err_type); 
void stripln(char * string);
char * removeSpace(char * line, char * newLine, int index);
void fill_input_buffer(char *input_buffer);
#endif
