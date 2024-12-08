#ifndef HISTORY_H
#define HISTORY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define MAX_HISTORY 100
#define MAX_COMMAND_LENGTH 1024

// Command history
extern char *history[MAX_HISTORY];
extern int history_count;
extern int history_index;

void enableRawMode(struct termios *original);
void disableRawMode(struct termios *original);
void add_to_history(const char *command);
void handle_up_arrow(char *buffer, int *cursor);
void handle_down_arrow(char *buffer, int *cursor);
#endif