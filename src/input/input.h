#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#include "keys.h"
#include "mouse.h"

typedef enum {
    KEY,
    MOUSE,
} Event;

typedef struct {
    Event event; // Type of input
    union {
        Mouse mouse; // Mouse event data
        Key key; // Keyboard event data
    } data; // Union to hold either mouse or keyboard data
} Input;

void enable_mouse_support();
void disable_mouse_support();

void read_stdin(Input* input);

#endif // INPUT_H
