#include <ncurses.h>
#include <unistd.h> // ssize_t
#include <string.h> // memcpy()
#include <sys/select.h> // select()

#include "input.h"

void enable_mouse_support() {
    //printf("\x1b[?1l"); // Re-activate normal mode (instead of application mode)
    printf("\033[?1002h\n"); // Makes the terminal report mouse movement events
    printf("\033[?1003h\n"); // Makes the terminal report mouse movement events
    printf("\033[?1015h\n"); // Enable urxvt Mouse mode. (For terminals that understand this.)
    printf("\033[?1006h\n"); // Makes the terminal report mouse movement events
}

void disable_mouse_support() {
    //printf("\x1b[?1h"); // Disable normal mode
    printf("\033[?1002l\n"); // Disable mouse movement events, as l = low
    printf("\033[?1003l\n"); // Disable mouse movement events, as l = low
    printf("\033[?1015l\n"); // Disable mouse movement events, as l = low
    printf("\033[?1006l\n"); // Disable mouse movement events, as l = low
}

void read_stdin(Input* input) {
    const int STDIN = 0;
    int fd = STDIN;
    char buffer[100];
    fd_set readfds;
    struct timeval timeout;

    // Set up the file descriptor set
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    // Set the timeout
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000; // 1 second = 1000000 microseconds

    // Wait for data to be available
    int result = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (result == -1) {
        // Error
        input->event = MOUSE;
        //memcpy(input->data.key.code, [-1], 1);
    } else if (result == 0) {
        // Timeout
        input->event = MOUSE;
        //input->data.key = -2;
    } else {
        // Data is available to read
        ssize_t bytesRead = read(fd, input->data.key.code, sizeof(buffer) - 1);
        if (bytesRead < 1) {
            input->event = MOUSE;
            //input->data.key = -3;
        } else {
            input->event = KEY;
            input->data.key.length = bytesRead;
            //printf("0x%02X 0x%02X 0x%02X 0x%02X\n", buffer[0], buffer[1], buffer[2], buffer[3]);
            //memcpy(&(input->data.key.code), &buffer, bytesRead);
        }
    }
}
