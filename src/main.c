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
    short size = read_book(contacts, *file);
    if (size > 15 || !data_validation(contacts)) {
        (size > 15) ? puts("Phonebook has overflowed\n") : puts("");
        (size > 15) ? red_text("Data overflow\n") : puts("");
        red_text("Data validation failed\n");
        fclose(*file);
        exit(1);
    }
}

int main() {
    FILE *file;
    wrapper_contact contacts;
    data_setup(contacts.list, &file);
    bool running = true;
    short option;
    char type[10];

    while (running) {
        display_menu();
        puts("Enter an option: ");
        char buffer[10];
        if (fgets(buffer, 10, stdin) == NULL) {
            puts("Exit key pressed\n");
            fclose(file);
            exit(1);
        }
        option = atoi(buffer);
        switch (option) {
            case 1:
                if (!add_contact(&contacts)) {
                    puts("There might be an error with the source file\n");
                }
                break;
            case 2:
                if (!delete_contact(&contacts)) {
                    puts("There might be an error with the source file\n");
                }
                break;
            case 3:
                puts("Search contact\n");
                break;
            case 4:
                puts("Do you want to filter by type?");
                puts("Write Business, Personal, Office (or 0, 1, 2)\
                 to filter by type");
                 puts("Write any other key to display all contacts");
                if (fgets(type, 10, stdin) == NULL) {
                    display_all_contacts(&contacts, -1);
                }
                display_all_contacts(&contacts, getFilterType(type));
                break;
            case 5:
                running = false;
                break;
            default:
                puts("Invalid option!\n");
                break;
        }
    }
    return 0;
}
