#include "tools.h"
#include "contact_handling.h"

bool add_contact(wrapper_contact *contacts) {
    if (contacts->size >= 15) {
        puts("Phonebook is full\n");
        return false;
    }
    contact new_contact = contact_form();
    if (new_contact.name == NULL || new_contact.phone == NULL ||
        new_contact.email == NULL || new_contact.type == UNKNOWN ||
        strchr(new_contact.email, '@') == NULL) {
            red_text("Invalid contact information\n");
        return false;
    }
    if (check_duplicate(contacts, new_contact)) {
        red_text("Duplicate contact found\n");
        return false;
    }
    for (int i = 0; i < 15; i++) {
        if (contacts->list[i].name == NULL) {
            contacts->list[i] = new_contact;
            contacts->size++;
            contacts->modified = true;
            return true;
        }
    }
    red_text("Could not add contact\n");
    return false;
}

bool delete_contact(wrapper_contact *contacts) {
    puts("Enter name to delete: ");
    char name[50];
    char *processed_name;
    if (fgets(name, 50, stdin) == NULL) {
        puts("Could not read name\n");
        return false;
    }
    processed_name = pure_text(name);
    for (int i = 0; i < 15; i++) {
        if (contacts->list[i].name == NULL) {
            continue;
        }
        if (strcmp(contacts->list[i].name, processed_name) == 0) {
            puts("You are about to delete the following contact:");
            contact_print(contacts->list[i], true);
            puts("Are you sure you want to delete this contact? (y/[n])");
            char buffer[10];
            if (fgets(buffer, 10, stdin) == NULL) {
                puts("Could not read input\n");
                free(processed_name);
                return false;
            }
            if (buffer[0] != 'y') {
                puts("Contact not deleted\n");
                free(processed_name);
                return false;
            }
            contacts->list[i].name = NULL;
            contacts->list[i].phone = NULL;
            contacts->list[i].email = NULL;
            contacts->size--;
            adjust_index(contacts, i);
            contacts->modified = true;
            free(processed_name);
            return true;
        }
    }
    free(processed_name);
    puts("Contact not found\n");
    return false;
}

bool edit_contact(wrapper_contact *contacts) {
    puts("Enter name to edit: ");
    char name[50];
    if (fgets(name, 50, stdin) == NULL) {
        puts("Could not read name\n");
        return false;
    }
    char *processed_name = pure_text(name);
    for (int i = 0; i < 15; i++) {
        if (contacts->list[i].name == NULL) {
            continue;
        }
        if (lazyMatch(contacts->list[i].name, processed_name)) {
            puts("You are about to edit the following contact:");
            contact_print(contacts->list[i], true);
            contact new_contact = contact_form();
            if (new_contact.name == NULL || new_contact.phone == NULL ||
                    new_contact.email == NULL || new_contact.type == UNKNOWN) {
                red_text("Invalid contact information\n");
                free(processed_name);
                return false;
            }
            contacts->list[i] = new_contact;
            contacts->modified = true;
            free(processed_name);
            return true;
        }
    }
    puts("Contact not found\n");
    free(processed_name);
    return false;
}

bool search_contact(wrapper_contact *contacts) {
    puts("Enter name to search: ");
    char name[50];
    if (fgets(name, 50, stdin) == NULL) {
        puts("Could not read name\n");
        return false;
    }
    char *processed_name = pure_text(name);
    for (int i = 0; i < 15; i++) {
        if (contacts->list[i].name == NULL) {
            continue;
        }
        if (lazyMatch(contacts->list[i].name, processed_name)) {
            puts("Contact found:");
            contact_print(contacts->list[i], true);
            free(processed_name);
            return true;
        }
    }
    free(processed_name);
    puts("Contact not found\n");
    return false;
}
