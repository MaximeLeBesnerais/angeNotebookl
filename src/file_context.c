#include "file_context.h"

file_context* create_file_context(const char* filename) {
    file_context* ctx = malloc(sizeof(file_context));
    ctx->filename = strdup(filename);
    ctx->is_open = false;
    ctx->handle = NULL;
    return ctx;
}

bool open_file(file_context* ctx, const char* mode) {
    if (ctx->is_open) {
        fclose(ctx->handle);
    }
    ctx->handle = fopen(ctx->filename, mode);
    ctx->is_open = (ctx->handle != NULL);
    return ctx->is_open;
}

void close_file(file_context* ctx) {
    if (ctx->is_open) {
        fclose(ctx->handle);
        ctx->is_open = false;
    }
}
