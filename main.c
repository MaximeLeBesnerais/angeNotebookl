#include "helpers.h"

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
    read_book(contacts, *file);
    if (!data_validation(contacts)) {
        red_text("Data validation failed\n");
        fclose(*file);
        exit(1);
    }
}

int main() {
    FILE *file;
    contact contacts[15];
    data_setup(contacts, &file);
    return 0;
}
