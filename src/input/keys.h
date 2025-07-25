#ifndef KEYS_H
#define KEYS_H

typedef enum {
    ESCAPE,
    ARROW_RIGHT,
} Code;

typedef struct {
    char code[100];
    int length;
} Key;

extern Key keys[100];

#endif // KEYS_H
