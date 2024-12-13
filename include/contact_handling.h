#ifndef CONTACT_HANDLING_H_
#define CONTACT_HANDLING_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
    BUSINESS,
    PERSONAL,
    OFFICE,
    UNKNOWN
} contact_type;

typedef struct
{
    char *name;
    char *phone;
    contact_type type;
    char *email;
} contact;

typedef struct wrapper_contact_s
{
    contact list[15];
    short size;
} wrapper_contact;


char *printType(contact_type type);
void contact_print(contact contacts);
short read_book(contact *contacts, FILE *file);
bool data_validation(contact *contacts);
void print_book(wrapper_contact *contacts);
bool add_contact(wrapper_contact *contacts);
bool delete_contact(wrapper_contact *contacts);
void display_all_contacts(wrapper_contact *contacts, int filter);
bool edit_contact(wrapper_contact *contacts);

#endif /* CONTACT_HANDLING_H_ */
