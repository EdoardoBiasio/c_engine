#pragma once

#include "utils/memory.h"

typedef struct texture_t {
    GLuint id;
} texture_t;

texture_t* texture_create(const char* file_path);
void texture_destroy(texture_t* texture);
