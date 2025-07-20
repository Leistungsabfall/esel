#include <unistd.h> // read()

#include "input.h"

const int MOUSE = 0;
const int KEY = 1;

void read_stdin(Input* input) {
    char buffer[1024] = {0};
    int size = read(0, buffer, sizeof(buffer) - 1);
    // if (size == -1) {
    //     return NULL;
    // }

    // Check for ESC
    if (size == 1 && buffer[0] == ESCAPE) {
        input->type = KEY;
        input->key = ESCAPE;
    }

    // pretty_print_buffer(buffer, size);
}
