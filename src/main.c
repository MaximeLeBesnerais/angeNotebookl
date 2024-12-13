#include "tools.h"
#include "contact_handling.h"

void data_setup(contact contacts[], FILE **file)
{
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

bool write_to_file(contact contacts[], FILE *file) {
    fclose(file);
    file = fopen("contacts_book.csv", "w+");
    if (file == NULL) {
        red_text("Critical error opening file\n");
        exit(1);
    }
    rewind(file);
    for (int i = 0; i < 15; i++) {
        if (contacts[i].name == NULL)
            continue;
        fprintf(file, "%s, %s, %d, %s\n", contacts[i].name, contacts[i].phone,
                contacts[i].type, contacts[i].email);
    }
    fclose(file);
    file = fopen("contacts_book.csv", "a+");
    return true;
}

void exit_process(wrapper_contact contacts, FILE *file) {
    puts("Exit key pressed\n");
    if (contacts.modified) {
        write_to_file(contacts.list, file);
        puts("All contacts saved\n");
    }
    for (int i = 0; i < 15; i++)
    {
        if (contacts.list[i].name != NULL)
        {
            free(contacts.list[i].name);
            free(contacts.list[i].phone);
            free(contacts.list[i].email);
        }
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
            exit_process(contacts, file);
            running = false;
            break;
        }
        clear_screen();
        option = atoi(buffer);
        switch (option) {
        case 1:
            add_contact(&contacts);
            break;
        case 2:
            delete_contact(&contacts);
            break;
        case 3:
            edit_contact(&contacts);
            break;
        case 4:
            puts("Do you want to filter by type?");
            puts("Write 1 for Business, 2 for Personal, 3 for Office,"
                 " or any other key for all contacts");
            if (fgets(type, 10, stdin) == NULL)
                display_all_contacts(&contacts, UNKNOWN);
            display_all_contacts(&contacts, getFilterType(type));
            break;
        case 5:
            running = false;
            exit_process(contacts, file);
            break;
        default:
            puts("Invalid option!\n");
            break;
        }
        buffer[0] = '\0';
    }
    fclose(file);
    return 0;
}
