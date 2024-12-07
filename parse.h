#ifndef PARSE_H
#define PARSE_H
int parse_args( char * line, char ** arg_ary ); //parse the args for execvp
void parse_lines(char * input, char ** line_ary); //parses set of semicolon seperated lines into ary
void parse_opps(char * line, char ** opp_seperated_ary, int * size); //parse a cmd sequence with redirects into a ary
void sep_on_first_char(char * line, char * mv_line, char * sep_on);//finds the first example of < | or > in line and passes it into sep_on
#endif
