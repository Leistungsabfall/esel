#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <ncurses.h>

typedef struct {
    int lines;
    int cols;
    WINDOW* widget;
} TextArea;

void init_textarea(TextArea* textarea);

#endif // TEXTAREA_H
