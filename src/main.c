#include "tools.h"
#include "contact_handling.h"
#include "file_context.h"

short data_setup(contact contacts[], FILE **file) {
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
    return size;
}

bool write_to_file(contact contacts[], file_context *ctx) {
    if (!open_file(ctx, "w+")) {
        red_text("Critical error opening file\n");
        exit(1);
    }
    for (int i = 0; i < 15; i++) {
        if (contacts[i].name == NULL)
            continue;
        fprintf(ctx->handle, "%s, %s, %d, %s\n", contacts[i].name, contacts[i].phone,
                contacts[i].type, contacts[i].email);
    }
    close_file(ctx);
    return open_file(ctx, "a+");
}

void exit_process(wrapper_contact contacts, file_context *ctx) {
    puts("Exit key pressed\n");
    if (contacts.modified) {
        write_to_file(contacts.list, ctx);
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
    clear_screen();
    file_context *file_ctx = create_file_context("contacts_book.csv");
    wrapper_contact contacts;
    if (!open_file(file_ctx, "a+")) {
        red_text("Error creating file context\n");
        free(file_ctx);
        return(1);
    }
    short size = data_setup(contacts.list, &file_ctx->handle);
    contacts.size = size;
    bool running = true;
    short option;
    char type[10];
    green_text("Welcome to the Phonebook\n");

    while (running) {
        display_menu();
        puts("Enter an option: ");
        char buffer[10];
        if (fgets(buffer, 10, stdin) == NULL) {
            exit_process(contacts, file_ctx);
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
            exit_process(contacts, file_ctx);
            break;
        default:
            puts("Invalid option!\n");
            break;
        }
        buffer[0] = '\0';
        puts("Press any key to continue...");
        getchar();
        clear_screen();
    }
    if (file_ctx) {
        close_file(file_ctx);
        free(file_ctx->filename);
        free(file_ctx);
    }
    return 0;
}
