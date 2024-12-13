#include "tools.h"

contact_type getFilterType(char *type) {
    int temp = atoi(type);
    if (temp == 1) {
        return BUSINESS;
    } else if (temp == 2) {
        return PERSONAL;
    } else if (temp == 3) {
        return OFFICE;
    }
    return UNKNOWN;
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
