[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Tfg6waJb)
# It's Easy as A(vrahami) B(ellows) C(hen)
#### Michael Avrahami, Abel Bellows, Matthew Chen

## Features
1. Input Processing
   - Reads one line at a time from stdin
   - Parses separate commands on semicolons
   - Runs (each) command by forking and execvp-ing
2. User Prompting
   - Prompts the user by printing the cwd and a $ sign
   - Uses the ~ to shorten the cwd if the home directory is in the path
3. Exiting
   - ctrl+D and "exit" both exit the shell
4. CD
   - Supports cd to change the current directory
5. Redirection
   - Supports < | and > symbols
   - < must be the first of the redirection symbols in a command, and > must be the last of the redirection symbols in a command
   - a < b | c > d is the maximum redirection capabilities supported
6. History
   - Suports scrolling through previous commands via up/down arrows

## Attempted features and bugs

attempted to support history and scrolling through history with cntrl + \ (see branch history)
attempted to support parsing any redirection sequence.

any invalid commands or weird characters will create a buggy shell
 
## Function headers
```
int parse_args( char * line, char ** arg_ary );
void parse_lines(char * input, char ** line_ary);
void parse_opps(char * line, char ** opp_seperated_ary, int * size);
void sep_on_first_char(char * line, char * sep_on);

void prompt_print();

int redirect_stdout(int fd);
int redirect_stdout_create_file(char * name);
int redirect_stdin(int fd);
int redirect_stdin_create_file(char * name);
void reset_stdin(int old_stdin);
void reset_stdout(int old_stdout);

void flow_execution(char ** chunks, int index, int size, struct sigaction old);
int run_cmd(char * cmd_block,struct sigaction old);

int special_cmd(char ** arg_ary);
void sighandler(int signo);

int check_err(int err, char * err_type); 
void stripln(char * string);
char * removeSpace(char * line, char * newLine, int index);

void enableRawMode(struct termios *original);
void disableRawMode(struct termios *original);
void add_to_history(const char *command);
void handle_up_arrow(char *buffer, int *cursor);
void handle_down_arrow(char *buffer, int *cursor);
void fill_input_buffer(char *input_buffer);
```

