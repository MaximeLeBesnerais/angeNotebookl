#include "helpers.h"

int main() {
    FILE *file = fopen("contacts_book.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    contact contacts[15];
    read_book(contacts, file);
    if (!data_validation(contacts)) {
        // in red, data validation failed
        printf("\033[1;31m Data validation failed\n");
        // reset color
        printf("\033[0m");
        return 1;
    }

    return 0;
}
