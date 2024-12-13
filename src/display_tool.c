#include "tools.h"

void red_text(char *text) {
    puts("\033[1;31m");
    puts(text);
    puts("\033[0m");
}

void green_text(char *text) {
    puts("\033[1;32m");
    puts(text);
    puts("\033[0m");
}

void blue_text(char *text) {
    puts("\033[1;34m");
    puts(text);
    puts("\033[0m");
}

void display_menu() {
    puts("1. Add contact");
    puts("2. Delete contact");
    puts("3. Edit contact");
    puts("4. Search contact");
    puts("5. Display all contacts");
    puts("6. Exit");
}

void clear_screen() {
    printf("\033[2J\033[1;1H");  // Clear screen and move cursor to top-left
    fflush(stdout);
}
