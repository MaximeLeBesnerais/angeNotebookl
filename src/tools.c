#include "helpers.h"

void red_text(char *text) {
    puts("\033[1;31m");
    puts(text);
    puts("\033[0m");
}
