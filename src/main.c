#include "helpers.h"

void data_setup(contact contacts[], FILE **file) {
    *file = fopen("contacts_book.csv", "a+");
    if (*file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    for (int i = 0; i < 15; i++) {
        contacts[i].name = NULL;
        contacts[i].phone = NULL;
        contacts[i].email = NULL;
    }
    read_book(contacts, *file);
    if (!data_validation(contacts)) {
        red_text("Data validation failed\n");
        fclose(*file);
        exit(1);
    }
}

void display_menu() {
    printf("1. Add contact\n");
    printf("2. Delete contact\n");
    printf("3. Search contact\n");
    printf("4. Display all contacts\n");
    printf("5. Exit\n");
}

int main() {
    FILE *file;
    contact contacts[15];
    data_setup(contacts, &file);
    bool running = true;
    while (running) {
    }
    return 0;
}
