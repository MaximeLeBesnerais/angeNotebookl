#include "tools.h"
#include "contact_handling.h"

char *printType(contact_type type) {
    switch (type) {
    case BUSINESS:
        return "Business";
    case PERSONAL:
        return "Personal";
    case OFFICE:
        return "Office";
    default:
        return "Unknown";
    }
}

void contact_print(contact contacts, bool print_all) {
    printf("%s: %s", contacts.name, contacts.phone);
    if (print_all) {
        printf(", %s, %s\n", printType(contacts.type), contacts.email);
    } else {
        putchar('\n');
    }
}

void print_book(wrapper_contact *contacts) {
    for (int i = 0; i < 15; i++) {
        if (contacts->list[i].name == NULL) {
            continue;
        }
        printf("Index: %d", i + 1);
        contact_print(contacts->list[i], true);
    }
}

short read_book(contact *contacts, FILE *file) {
    char line[1024];
    int i = 0;
    int temp = 0;
    while (fgets(line, 1024, file)) {
        char *name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *type = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        contacts[i].name = malloc(strlen(name) + 1);
        strcpy(contacts[i].name, name);
        contacts[i].phone = malloc(strlen(phone) + 1);
        strcpy(contacts[i].phone, phone);
        temp = atoi(type);
        if (temp < 0 || temp > 2) {
            contacts[i].type = UNKNOWN;
        } else {
            contacts[i].type = (contact_type)temp;
        }
        contacts[i].email = malloc(strlen(email) + 1);
        // remove newline character if present
        if (email[strlen(email) - 1] == '\n') {
            email[strlen(email) - 1] = '\0';
        }
        strcpy(contacts[i].email, email);
        i++;
    }
    return i;
}

bool data_validation(contact *contacts) {
    for (int i = 0; i < 15; i++) {
        if (contacts[i].name == NULL) {
            continue;
        }
        for (int j = i + 1; j < 15; j++) {
            if (contacts[j].name == NULL) {
                continue;
            }
            if (strcmp(contacts[i].name, contacts[j].name) == 0 || 
                strcmp(contacts[i].phone, contacts[j].phone) == 0) {
                    contact_print(contacts[i], true);
                    printf("Name and phone number must be unique\n");
                return false;
            }
        }
        if (strchr(contacts[i].email, '@') == NULL) {
            contact_print(contacts[i], true);
            printf("Email must contain '@'\n");
            return false;
        }
    }
    return true;
}

contact contact_form() {
    contact new_contact;
    new_contact.name = malloc(50);
    new_contact.phone = malloc(15);
    new_contact.email = malloc(50);
    puts("Enter contact information in the following format:"\
    " Name, Phone, [1 for Business, 2 for Personal, 3 for Office], Email");
    char buffer[1024];
    if (fgets(buffer, 1024, stdin) == NULL) {
        puts("Could not read contact information\n");
        return new_contact;
    }
    char *name = strtok(buffer, ",");
    char *phone = strtok(NULL, ",");
    char *type = strtok(NULL, ",");
    char *email = strtok(NULL, ",");
    strcpy(new_contact.name, name);
    strcpy(new_contact.phone, phone);
    int type_int = atoi(type);
    if (type_int < 0 || type_int > 2) {
        puts("Invalid contact type\n");
        new_contact.type = UNKNOWN;
    }
    strcpy(new_contact.email, email);
    return new_contact;
}

bool add_contact(wrapper_contact *contacts) {
    if (contacts->size == 15) {
        puts("Phonebook is full\n");
        return false;
    }
    contact new_contact = contact_form();
    if (new_contact.name == NULL || new_contact.phone == NULL ||
        new_contact.email == NULL || new_contact.type == UNKNOWN) {
            red_text("Invalid contact information\n");
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

void adjust_index(wrapper_contact *contacts, short index) {
    for (int i = index; i < 15; i++) {
        if (contacts->list[i + 1].name == NULL) {
            contacts->list[i].name = NULL;
            contacts->list[i].phone = NULL;
            contacts->list[i].email = NULL;
            contacts->size--;
            return;
        }
        contacts->list[i] = contacts->list[i + 1];
    }
}

bool delete_contact(wrapper_contact *contacts) {
    puts("Enter name to delete: ");
    char name[50];
    if (fgets(name, 50, stdin) == NULL) {
        puts("Could not read name\n");
        return false;
    }
    for (int i = 0; i < 15; i++) {
        if (contacts->list[i].name == NULL) {
            continue;
        }
        if (strcmp(contacts->list[i].name, name) == 0) {
            contacts->list[i].name = NULL;
            contacts->list[i].phone = NULL;
            contacts->list[i].email = NULL;
            contacts->size--;
            adjust_index(contacts, i);
            contacts->modified = true;
            return true;
        }
    }
    puts("Contact not found\n");
    return false;
}

void display_all_contacts(wrapper_contact *contacts, contact_type filter) {
    for (int i = 0; i < 15; i++) {
        if (contacts->list[i].name == NULL) {
            continue;
        }
        if ((filter != UNKNOWN) && (contacts->list[i].type != filter)) {
            continue;
        }
        contact_print(contacts->list[i], (filter == UNKNOWN));
    }
}

bool edit_contact(wrapper_contact *contacts) {
    puts("Enter name to edit: ");
    char name[50];
    if (fgets(name, 50, stdin) == NULL) {
        puts("Could not read name\n");
        return false;
    }
    for (int i = 0; i < 15; i++) {
        if (contacts->list[i].name == NULL) {
            continue;
        }
        if (strcmp(contacts->list[i].name, name) == 0) {
            contact new_contact = contact_form();
            if (new_contact.name == NULL || new_contact.phone == NULL ||
                new_contact.email == NULL || new_contact.type == UNKNOWN) {
                    red_text("Invalid contact information\n");
                return false;
            }
            contacts->list[i] = new_contact;
            return true;
        }
    }
    puts("Contact not found\n");
    return false;
}
