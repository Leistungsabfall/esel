#include "textarea.h"

void init_textarea(TextArea* textarea) {
    textarea->cols = COLS - 2;
    textarea->lines = LINES - 2;
    textarea->widget = newwin(LINES, COLS, 0, 0);
    // Clear the textarea
    wclear(textarea->widget);
    box(textarea->widget, 0, 0); // Draw a box around the textarea
    wrefresh(textarea->widget);
    refresh(); // TODO: outsource, even needed?
    clear(); // TODO: outsource, even needed?
    //keypad(textarea->widget, TRUE);   // Enable function keys and arrow keys
}
