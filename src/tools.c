#include "tools.h"

void red_text(char *text) {
    puts("\033[1;31m");
    puts(text);
    puts("\033[0m");
}

void display_menu() {
    printf("1. Add contact\n");
    printf("2. Delete contact\n");
    printf("3. Search contact\n");
    printf("4. Display all contacts\n");
    printf("5. Exit\n");
}
