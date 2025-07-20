#include <ncurses.h>
#include <stdio.h> // printf()
#include <string.h> // strlen()
#include <unistd.h> // read()

#include "input.h"

void enable_mouse_support() {
    printf("\033[?1002h\n"); // Makes the terminal report mouse movement events
    printf("\033[?1003h\n"); // Makes the terminal report mouse movement events
    printf("\033[?1015h\n"); // Enable urxvt Mouse mode. (For terminals that understand this.)
    printf("\033[?1006h\n"); // Makes the terminal report mouse movement events
}

void disable_mouse_support() {
    printf("\033[?1002l\n"); // Disable mouse movement events, as l = low
    printf("\033[?1003l\n"); // Disable mouse movement events, as l = low
    printf("\033[?1015l\n"); // Disable mouse movement events, as l = low
    printf("\033[?1006l\n"); // Disable mouse movement events, as l = low
}

void read_stdin(Input* input) {
    char buffer[1024] = {0};
    int size = read(0, buffer, sizeof(buffer) - 1);
//     if (size == -1) {
//         input->type = INVALID;
//     } TODO
//
    // Check for ESC
    if (size == 1 && buffer[0] == ESCAPE) {
        input->type = KEY;
        input->data.key.key.key = ESCAPE;
    }
}
