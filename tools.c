#include "helpers.h"

void contact_print(contact *contacts) {
    for (int i = 0; i < 15; i++) {
        printf("Name: %s; Phone: %s; Type: %d; Email: %s\n", contacts[i].name, 
        contacts[i].phone, contacts[i].type, contacts[i].email);
    }
}

void read_book(contact *contacts, FILE *file) {
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
}

bool data_validation(contact *contacts) {
    for (int i = 0; i < 15; i++) {
        for (int j = i + 1; j < 15; j++) {
            if (strcmp(contacts[i].name, contacts[j].name) == 0 || 
                strcmp(contacts[i].phone, contacts[j].phone) == 0) {
                    contact_print(contacts);
                    printf("Name and phone number must be unique\n");
                return false;
            }
        }
        if (strchr(contacts[i].email, '@') == NULL) {
            contact_print(contacts);
            printf("Email must contain '@'\n");
            return false;
        }
    }
    return true;
}