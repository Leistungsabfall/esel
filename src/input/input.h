#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#include "keys.h"

typedef enum {
    KEY,
    MOUSE,
} InputType;

typedef struct {
    Key key;
} KeyPress;

typedef struct {
    int x;
    int y;
    bool pressed;
} MouseEvent;

typedef struct {
    InputType type; // Type of input
    union {
        MouseEvent mouse; // Mouse event data
        KeyPress key; // Keyboard event data
    } data; // Union to hold either mouse or keyboard data
} Input;

void enable_mouse_support();
void disable_mouse_support();

void read_stdin(Input* input);

#endif // INPUT_H
