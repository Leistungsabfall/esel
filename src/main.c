#include <ncurses.h>
#include <stdbool.h>
#include <string.h>

#include "input/input.h"
#include "widgets/textarea.h"

// #define UNUSED(x) (void)(x)

int screen_height, screen_width;

void handle_resize(TextArea* textarea) {
    screen_height = LINES;
    screen_width = COLS;
    textarea->cols = COLS - 2;
    textarea->lines = LINES - 2;
}

void display_text(TextArea* textarea, char* text) {
    wclear(textarea->widget);
    box(textarea->widget, 0, 0);

    mvwprintw(textarea->widget, 1, 1, "%s", text);

    // Move the cursor to the correct position
    //wmove(textarea->widget, current_line - scroll_offset + 1, cursor_pos + 1);
    wrefresh(textarea->widget);
}

void store_debug_output(char* text, Input* input) {
    sprintf(text, "Input: Event: %d Length: %d Code [", input->event, input->data.key.length);
    for (int i=0; i<input->data.key.length;i++) {
        sprintf(text + strlen(text), " 0x%02X ", input->data.key.code[i]);
    }
    sprintf(text + strlen(text), "]\n");
}

int main() {
    initscr();              // Initialize ncurses
    cbreak();               // Disable line buffering
    noecho();               // Don't echo input
    keypad(stdscr, FALSE);  // Explicitly enable normal mode
    //mousemask(ALL_MOUSE_EVENTS, NULL); // Enable mouse events
    timeout(0);             // Set a timeout for getch() (milliseconds)
    refresh();
    screen_height = LINES;
    screen_width = COLS;

    TextArea textarea;
    init_textarea(&textarea);

    /*char text[1000][1000] = {}; // Array to hold text lines
    int current_line = 0;
    int cursor_pos = 0; // Position of the cursor in the current line
    int scroll_offset = 0; // Number of lines scrolled
    int ch;*/

    enable_mouse_support();
    Input input = {
        .event = MOUSE,
        .data.key.length = 0,
    };
    char text[1024];
    while (true) {
        read_stdin(&input);
        store_debug_output(text, &input);
        display_text(&textarea, text);
        if (input.event == KEY) {
            if (keys[ESCAPE].length == input.data.key.length && memcmp(&keys[ESCAPE], &input.data.key.code, input.data.key.length) == 0) {
                break;
            }
        }



        /*
        // display_text(&textarea, text, current_line, cursor_pos, scroll_offset);
        // ch = wgetch(textarea.widget);

        if (ch == ERR) {
            // timeout, continue event loop

        }

        // Check for mouse events
        if (ch == KEY_MOUSE) {
            MEVENT event;
            if (getmouse(&event) != OK) {
                continue;
            }
            // Check if the mouse wheel is used
            if (event.bstate & BUTTON4_PRESSED && scroll_offset > 0) {
                scroll_offset--;
            }
            if (event.bstate & BUTTON5_PRESSED && scroll_offset < screen_height -1) {
                scroll_offset++;
            }
            continue;
        }

        switch (ch) {
            case KEY_RESIZE:
                handle_resize(&textarea);
                break;
            case KEY_UP:
                if (current_line > 0) {
                    current_line--;
                    cursor_pos = strlen(text[current_line]); // Move cursor to the end of the line
                    if (current_line < scroll_offset) {
                        scroll_offset--; // Scroll up if needed
                    }
                }
                break;
            case KEY_DOWN:
                if (current_line < screen_height - 1) {
                    current_line++;
                    cursor_pos = strlen(text[current_line]); // Move cursor to the end of the line
                    if (current_line >= scroll_offset + screen_height) {
                        scroll_offset++; // Scroll down if needed
                    }
                }
                break;
            case KEY_BACKSPACE: // Handle backspace
            // case 127: // Handle backspace
                if (cursor_pos > 0) {
                    // Shift characters to the left
                    memmove(&text[current_line][cursor_pos - 1], &text[current_line][cursor_pos], strlen(text[current_line]) - cursor_pos + 1);
                    cursor_pos--; // Move cursor left
                }
                break;
            case '\n':
                if (current_line < screen_height - 1) {
                    current_line++;
                    cursor_pos = 0; // Move cursor to the start of the new line
                }
                if (current_line == screen_height - 1) {
                    break;
                    current_line++;
                    cursor_pos = 0;
                    scroll_offset++;
                }
                break;
            case KEY_LEFT:
                if (cursor_pos > 0) {
                    cursor_pos--; // Move cursor left
                }
                break;
            case KEY_RIGHT:
                if ((long unsigned int) cursor_pos < strlen(text[current_line])) {
                    cursor_pos++; // Move cursor right
                }
                break;
            case 27: // Escape key
                // Check if there is another input waiting
                ch = getch();
                if (ch == ERR || ch == 27) {
                    goto end; // No other input or another Escape key press, exit the program
                } else {
                    // Handle additional input if needed
                    break; // Continue to process other keys
                }
            default:
                if (ch >= 32 && ch <= 126) { // Printable characters
                    if (cursor_pos < screen_width - 1) {
                        // Shift characters to the right
                        memmove(&text[current_line][cursor_pos + 1], &text[current_line][cursor_pos], strlen(text[current_line]) - cursor_pos + 1);
                        text[current_line][cursor_pos] = ch; // Insert character
                        cursor_pos++; // Move cursor right
                    }
                }
                break;
        }*/
    }

    delwin(textarea.widget);
    endwin(); // End ncurses mode
    disable_mouse_support();
    return 0;
}
