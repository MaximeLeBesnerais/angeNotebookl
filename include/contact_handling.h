#ifndef CONTACT_HANDLING_H_
#define CONTACT_HANDLING_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
    BUSINESS,
    PERSONAL,
    OFFICE
} contact_type;

typedef struct
{
    char *name;
    char *phone;
    contact_type type;
    char *email;
    short entry;
} contact;

char *printType(contact_type type);
void contact_print(contact contacts);
void read_book(contact *contacts, FILE *file);
bool data_validation(contact *contacts);

#endif /* CONTACT_HANDLING_H_ */