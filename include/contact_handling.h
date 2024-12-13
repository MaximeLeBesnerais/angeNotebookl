#ifndef CONTACT_HANDLING_H_
#define CONTACT_HANDLING_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum contact_type_s
{
    BUSINESS,
    PERSONAL,
    OFFICE,
    UNKNOWN
} contact_type;

typedef struct contact_s
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
    bool modified;
} wrapper_contact;


char *printType(contact_type type);
void contact_print(contact contacts, bool print_all);
short read_book(contact *contacts, FILE *file);
bool data_validation(contact *contacts);
//---------------------------------------------------------
bool add_contact(wrapper_contact *contacts);
bool delete_contact(wrapper_contact *contacts);
bool edit_contact(wrapper_contact *contacts);
bool search_contact(wrapper_contact *contacts);
//---------------------------------------------------------
contact contact_form();
void adjust_index(wrapper_contact *contacts, short index);
void display_all_contacts(wrapper_contact *contacts, contact_type filter);

#endif /* CONTACT_HANDLING_H_ */
