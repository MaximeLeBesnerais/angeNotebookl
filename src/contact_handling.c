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

bool lazyMatch(char *ref, char *match) {
    short ref_len = strlen(ref);
    short match_len = strlen(match);
    if (ref_len != match_len) {
        return false;
    }
    for (int i = 0; i < ref_len; i++) {
        if (ref[i] != match[i]) {
            return false;
        }
    }
    return true;
}

char *pure_text(char *text) {
    char *new_text = malloc(strlen(text) + 1);
    if (text[strlen(text) - 1] == '\n') {
        text[strlen(text) - 1] = '\0';
    }
    while (*text == ' ') {
        text++;
    }
    strcpy(new_text, text);
    return new_text;
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
                return false;
            }
            if (buffer[0] != 'y') {
                puts("Contact not deleted\n");
                return false;
            }
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
    short count = 1;
    // First print Office contacts except if filter is unknown or office
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
                return false;
            }
            contacts->list[i] = new_contact;
            contacts->modified = true;
            return true;
        }
    }
    puts("Contact not found\n");
    return false;
}
