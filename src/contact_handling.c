#include "tools.h"
#include "contact_handling.h"

contact contact_form() {
    contact new_contact;
    new_contact.name = malloc(50);
    new_contact.phone = malloc(15);
    new_contact.email = malloc(50);
    puts("Enter contact information in the following format:"\
    " Name, Phone, [1 for Business, 2 for Personal, 3 for Office], Email\n"\
    "Enter exit to cancel");
    char buffer[1024];
    if (fgets(buffer, 1024, stdin) == NULL) {
        puts("Could not read contact information\n");
        return new_contact;
    }
    if (lazyMatch(pure_text(buffer), "exit")) {
        new_contact.name = NULL;
        return new_contact;
    }
    if (strchr(buffer, ',') == NULL || strchr(strchr(buffer, ',') + 1, ',') == NULL ||
        strchr(strchr(strchr(buffer, ',') + 1, ',') + 1, ',') == NULL) {
        new_contact.name = NULL;
        return new_contact;
    }
    char *name = strtok(buffer, ",");
    char *phone = strtok(NULL, ",");
    char *type = strtok(NULL, ",");
    char *email = strtok(NULL, ",");
    strcpy(new_contact.name, pure_text(name));
    strcpy(new_contact.phone, pure_text(phone));
    int type_int = atoi(type);
    if (type_int < 1 || type_int > 3) {
        puts("Invalid contact type\n");
        new_contact.type = UNKNOWN;
    } else {
        new_contact.type = (contact_type)type_int;
    }
    strcpy(new_contact.email, pure_text(email));
    return new_contact;
}

void adjust_index(wrapper_contact *contacts, short index) {
    free(contacts->list[index].name);
    free(contacts->list[index].phone);
    free(contacts->list[index].email);
    for (int i = index; i < 14; i++) {
        if (contacts->list[i + 1].name == NULL) {
            contacts->list[i].name = NULL;
            contacts->list[i].phone = NULL;
            contacts->list[i].email = NULL;
            break;
        }
        contacts->list[i] = contacts->list[i + 1];
    }
    if (index < 14) {
        contacts->list[14].name = NULL;
        contacts->list[14].phone = NULL;
        contacts->list[14].email = NULL;
    }
}

void display_all_contacts(wrapper_contact *contacts, contact_type filter) {
    short count = 1;
    bool is_office = filter == OFFICE;
    bool is_personal = filter == PERSONAL;
    bool is_business = filter == BUSINESS;
    if (is_office|| filter == UNKNOWN) {
        blue_text("--- Office Contacts ---\n");
        for (int i = 0; i < 15; i++) {
            if (contacts->list[i].name == NULL) {
                continue;
            }
            if (contacts->list[i].type == OFFICE) {
                printf("%d. ", count);
                contact_print(contacts->list[i], !is_office);
                count++;
            }
        }
    }
    if (is_personal || filter == UNKNOWN) {
        blue_text("--- Personal Contacts ---\n");
        for (int i = 0; i < 15; i++) {
            if (contacts->list[i].name == NULL) {
                continue;
            }
            if (contacts->list[i].type == PERSONAL) {
                printf("%d. ", count);
                contact_print(contacts->list[i], !is_personal);
                count++;
            }
        }
    }
    if (is_business || filter == UNKNOWN) {
        blue_text("--- Business Contacts ---\n");
        for (int i = 0; i < 15; i++) {
            if (contacts->list[i].name == NULL) {
                continue;
            }
            if (contacts->list[i].type == BUSINESS) {
                printf("%d. ", count);
                contact_print(contacts->list[i], !is_business);
                count++;
            }
        }
    }
}
