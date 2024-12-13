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
    printf("1. Add contact\n");
    printf("2. Delete contact\n");
    printf("3. Edit contact\n");
    printf("4. Display all contacts\n");
    printf("5. Exit\n");
}

contact_type getFilterType(char *type) {
    int temp = atoi(type);
    if (temp == 1) {
        return BUSINESS;
    } else if (temp == 2) {
        return PERSONAL;
    } else if (temp == 3) {
        return OFFICE;
    }
    return UNKNOWN;
}

void clear_screen() {
    printf("\033[2J\033[1;1H");  // Clear screen and move cursor to top-left
    fflush(stdout);
}
