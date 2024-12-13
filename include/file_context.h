#ifndef FILE_CONTEXT_H
#define FILE_CONTEXT_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct file_context {
    FILE* handle;
    bool is_open;
    char* filename;
} file_context;

file_context* create_file_context(const char* filename);
bool open_file(file_context* ctx, const char* mode);
void close_file(file_context* ctx);

#endif // FILE_CONTEXT_H
