#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#include "keys.h"

extern const int MOUSE;
extern const int KEY;

typedef struct {
    int type;
    // Mouse
    int x;
    int y;
    bool pressed;
    // Key
    int key;
} Input;

void read_stdin(Input* input);

#endif // INPUT_H
