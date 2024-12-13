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

int getFilterType(char *type) {
    if (strcmp(type, "Business") == 0 || strcmp(type, "0") == 0) {
        return 0;
    } else if (strcmp(type, "Personal") == 0 || strcmp(type, "1") == 0) {
        return 1;
    } else if (strcmp(type, "Office") == 0 || strcmp(type, "2") == 0) {
        return 2;
    }
    return -1;
}
