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
        strcpy(contacts[i].name, pure_text(name));
        contacts[i].phone = malloc(strlen(phone) + 1);
        strcpy(contacts[i].phone, pure_text(phone));
        temp = atoi(type);
        if (temp < 0 || temp > 2) {
            contacts[i].type = UNKNOWN;
        } else {
            contacts[i].type = (contact_type)temp;
        }
        contacts[i].email = malloc(strlen(email) + 1);
        if (email[strlen(email) - 1] == '\n') {
            email[strlen(email) - 1] = '\0';
        }
        strcpy(contacts[i].email, pure_text(email));
        i++;
    }
    return i;
}

bool check_duplicate(wrapper_contact *contacts, contact new_contact) {
    for (int i = 0; i < 15; i++) {
        if (contacts->list[i].name == NULL) {
            continue;
        }
        if (lazyMatch(contacts->list[i].name, new_contact.name) ||
            lazyMatch(contacts->list[i].phone, new_contact.phone)) {
            return true;
        }
    }
    return false;
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
            if (lazyMatch(contacts[i].name, contacts[j].name) ||
                lazyMatch(contacts[i].phone, contacts[j].phone)) {
                contact_print(contacts[i], true);
                printf("Duplicate contact found\n");
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
