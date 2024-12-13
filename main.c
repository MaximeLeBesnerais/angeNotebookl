#include <string.h>

typedef enum {
    BUSINESS,
    PERSONAL,
    OFFICE
} contact_type;

typedef struct {
    char *name;
    char *phone;
    contact_type type;
    char *email;
} contact;

int main() {
    return 0;
}
