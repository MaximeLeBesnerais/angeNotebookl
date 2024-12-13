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

void contact_print(contact contacts) {
    printf("Name: %s, Phone: %s, Type: %s, Email: %s\n", contacts.name, 
    contacts.phone, printType(contacts.type), contacts.email);
}

short read_book(contact *contacts, FILE *file) {
    char line[1024];
    int i = 0;
    while (fgets(line, 1024, file)) {
        char *name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *type = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        contacts[i].name = malloc(strlen(name) + 1);
        strcpy(contacts[i].name, name);
        contacts[i].phone = malloc(strlen(phone) + 1);
        strcpy(contacts[i].phone, phone);
        contacts[i].type = atoi(type);
        contacts[i].email = malloc(strlen(email) + 1);
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
                    contact_print(contacts[i]);
                    printf("Name and phone number must be unique\n");
                return false;
            }
        }
        if (strchr(contacts[i].email, '@') == NULL) {
            contact_print(contacts[i]);
            printf("Email must contain '@'\n");
            return false;
        }
    }
    return true;
}

