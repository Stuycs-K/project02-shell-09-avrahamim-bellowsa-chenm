#ifndef UTIL_H
#define UTIL_H

//check if err occured and print if it did -- returns bool of whether err occured
int check_err(int err, char * err_type); 

//remove ln from string
void stripln(char * string);


char * removeSpace(char * line, char * newLine, int index);

#endif
