#include "tools.h"
#include "contact_handling.h"

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
    short option;

    while (running) {
        display_menu();
        puts("Enter an option: ");
        char buffer[10];
        if (fgets(buffer, 10, stdin) == NULL) {
            puts("Error reading input\n");
            fclose(file);
            exit(1);
        }
        option = atoi(buffer);
        switch (option) {
            case 1:
                puts("Add contact\n");
                break;
            case 2:
                puts("Delete contact\n");
                break;
            case 3:
                puts("Search contact\n");
                break;
            case 4:
                puts("Display all contacts\n");
                break;
            case 5:
                running = false;
                break;
            default:
                puts("Invalid option!\n");
                break;
        }
        for (int i = 0; i < 10; i++) {
            buffer[i] = 0;
        }
    }
    return 0;
}
