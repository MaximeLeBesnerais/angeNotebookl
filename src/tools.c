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
