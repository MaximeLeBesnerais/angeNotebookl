/*
 * Helpers Header File
 * Author: Angela Valencia
 * Description: Helper functions and utilities
 */

#ifndef HELPERS_H
#define HELPERS_H
#include <string.h>
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

void contact_print(contact contacts);
void read_book(contact *contacts, FILE *file);
bool data_validation(contact *contacts);
void red_text(char *text);

#endif // HELPERS_H