#ifndef PARSE_H
#define PARSE_H
void parse_args( char * line, char ** arg_ary ); //parse the args fir execvp
void parse_lines(char * input, char ** line_ary); //parses set of semicolon seperated lines into ary
void parse_opps(char * line, char ** opp_seperated_ary, int * size); //parse a cmd sequence with redirects into a ary
#endif
