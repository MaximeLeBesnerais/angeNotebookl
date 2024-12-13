/*
 * Helpers Header File
 * Author: Angela Valencia
 * Description: Helper functions and utilities
 */

#ifndef HELPERS_H
#define HELPERS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "contact_handling.h"

void red_text(char *text);
void green_text(char *text);
void blue_text(char *text);
void display_menu();
contact_type getFilterType(char *type);
void clear_screen();
bool lazyMatch(char *ref, char *match);
char *pure_text(char *text);

#endif // HELPERS_H
