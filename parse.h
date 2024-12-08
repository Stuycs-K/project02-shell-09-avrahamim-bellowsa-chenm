#ifndef PARSE_H
#define PARSE_H
int parse_args( char * line, char ** arg_ary );
void parse_lines(char * input, char ** line_ary);
void parse_opps(char * line, char ** opp_seperated_ary, int * size);
void sep_on_first_char(char * line, char * mv_line, char * sep_on);
#endif
