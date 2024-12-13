#include "helpers.h"

int main() {
    FILE *file = fopen("contacts_book.csv", "a+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    contact contacts[15];
    for (int i = 0; i < 15; i++) {
        contacts[i].name = NULL;
        contacts[i].phone = NULL;
        contacts[i].email = NULL;
    }

    read_book(contacts, file);
    if (!data_validation(contacts)) {
        printf("\033[1;31m Data validation failed\n");
        printf("\033[0m");
        fclose(file);
        return 1;
    }

    return 0;
}
