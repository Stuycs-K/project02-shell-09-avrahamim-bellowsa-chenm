#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "history.h"
#include "prompt.h"

char *history[MAX_HISTORY];
int history_count = 0;
int history_index = -1;

// Set terminal to raw mode
void enableRawMode(struct termios *original) {
    struct termios raw;
    tcgetattr(STDIN_FILENO, original);
    raw = *original;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// Restore original terminal settings
void disableRawMode(struct termios *original) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, original);
}

void add_to_history(const char *command) {
    if (history_count < MAX_HISTORY) {
        history[history_count++] = strdup(command);
    } else {
        free(history[0]);  // Remove oldest
        memmove(history, history + 1, (MAX_HISTORY - 1) * sizeof(char *));
        history[MAX_HISTORY - 1] = strdup(command);
    }
}

void handle_up_arrow(char *buffer, int *cursor) {
    if (history_index > 0) {
        history_index--;
        strcpy(buffer, history[history_index]);
        *cursor = strlen(buffer);
        printf("\r\033[K");  // Clear line and display command
        prompt_print();
        printf("%s", buffer);
        fflush(stdout);
    }
}

void handle_down_arrow(char *buffer, int *cursor) {
    if (history_index < history_count - 1) {
        history_index++;
        strcpy(buffer, history[history_index]);
        *cursor = strlen(buffer);
        printf("\r\033[K");  // Clear line and display command
        prompt_print();
        printf("%s", buffer);
        fflush(stdout);
    } else if (history_index == history_count - 1) {
        history_index++;
        buffer[0] = '\0';  // Clear command buffer
        *cursor = 0;
        printf("\r\033[K");
        prompt_print();
        printf("%s", buffer);
        fflush(stdout);
    }
}