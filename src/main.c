#include <ncurses.h>
#include <string.h>

#define MAX_LINES 20
#define MAX_COLS 80
#define VISIBLE_LINES 10 // Number of lines visible in the textarea

void init_textarea(WINDOW *textarea) {
    // Clear the textarea
    wclear(textarea);
    box(textarea, 0, 0); // Draw a box around the textarea
    wrefresh(textarea);
}

void display_text(WINDOW *textarea, char text[MAX_LINES][MAX_COLS], int current_line, int cursor_pos, int scroll_offset) {
    wclear(textarea);
    box(textarea, 0, 0);

    // Display only the visible lines based on the scroll offset
    for (int i = 0; i < VISIBLE_LINES; i++) {
        int line_index = scroll_offset + i;
        if (line_index < MAX_LINES && text[line_index][0] != '\0') {
            mvwprintw(textarea, i + 1, 1, "%s", text[line_index]);
        }
    }

    // Move the cursor to the correct position
    wmove(textarea, current_line - scroll_offset + 1, cursor_pos + 1);
    wrefresh(textarea);
}

int main() {
    initscr();              // Initialize ncurses
    cbreak();               // Disable line buffering
    noecho();               // Don't echo input
    mousemask(ALL_MOUSE_EVENTS, NULL); // Enable mouse events
    timeout(0);             // Set a timeout for getch() (milliseconds)
    refresh();

    WINDOW *textarea = newwin(VISIBLE_LINES + 2, MAX_COLS + 2, 1, 1);
    init_textarea(textarea);
    keypad(textarea, TRUE);   // Enable function keys and arrow keys

    char text[MAX_LINES][MAX_COLS] = {0}; // Array to hold text lines
    int current_line = 0;
    int cursor_pos = 0; // Position of the cursor in the current line
    int scroll_offset = 0; // Number of lines scrolled
    int ch;

    while (1) {
        display_text(textarea, text, current_line, cursor_pos, scroll_offset);
        ch = wgetch(textarea);

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
            if (event.bstate & BUTTON5_PRESSED && scroll_offset + VISIBLE_LINES < MAX_LINES -1) {
                scroll_offset++;
            }
            continue;
        }

        switch (ch) {
            case KEY_UP:
                if (current_line > 0) {
                    current_line--;
                    cursor_pos = strlen(text[current_line]); // Move cursor to the end of the line
                    if (cursor_pos < scroll_offset) {
                        scroll_offset--; // Scroll up if needed
                    }
                }
                break;
            case KEY_DOWN:
                if (current_line < VISIBLE_LINES - 1) {
                    current_line++;
                    cursor_pos = strlen(text[current_line]); // Move cursor to the end of the line
                    if (cursor_pos >= scroll_offset + VISIBLE_LINES) {
                        scroll_offset++; // Scroll down if needed
                    }
                }
                break;
            case KEY_BACKSPACE:
            case 127: // Handle backspace
                if (cursor_pos > 0) {
                    // Shift characters to the left
                    memmove(&text[current_line][cursor_pos - 1], &text[current_line][cursor_pos], strlen(text[current_line]) - cursor_pos + 1);
                    cursor_pos--; // Move cursor left
                }
                break;
            case '\n':
                if (current_line < VISIBLE_LINES - 1) {
                    current_line++;
                    cursor_pos = 0; // Move cursor to the start of the new line
                }
                break;
            case KEY_LEFT:
                if (cursor_pos > 0) {
                    cursor_pos--; // Move cursor left
                }
                break;
            case KEY_RIGHT:
                if (cursor_pos < strlen(text[current_line])) {
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
                    if (cursor_pos < MAX_COLS - 1) {
                        // Shift characters to the right
                        memmove(&text[current_line][cursor_pos + 1], &text[current_line][cursor_pos], strlen(text[current_line]) - cursor_pos + 1);
                        text[current_line][cursor_pos] = ch; // Insert character
                        cursor_pos++; // Move cursor right
                    }
                }
                break;
        }
    }

end:
    delwin(textarea);
    endwin(); // End ncurses mode
    return 0;
}
