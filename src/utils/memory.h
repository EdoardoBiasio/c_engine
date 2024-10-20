#pragma once

#include "../includes.h"
#include "logging.h"

enum malloc_type {
    M_STRING,
    M_MANAGED_PTR,
    M_SHADER,
    M_VAO,
    M_TEXTURE,
    M_MESH,
    M_CAMERA,
    M_LIGHT,
    M_UNUSED,
    M_NUM
};

void* bmalloc(u64 size, u16 type);
void bfree(void* mem, u64 size, u16 type);
void print_memory_stats();

typedef struct managed_ptr_t {
    void* mem;
    void (*deallocator) (void*);
    u32 size;
} managed_ptr_t;

#define managed_ptr_empty(type) (managed_ptr_t) { .mem = NULL, .size = sizeof(type), .deallocator = NULL }
#define managed_ptr_new(type) (managed_ptr_t) { .mem = bmalloc(sizeof(type), M_MANAGED_PTR), .size = sizeof(type), .deallocator = NULL }
#define managed_ptr_new_n(type, n) (managed_ptr_t) { .mem = bmalloc(sizeof(type) * n, M_MANAGED_PTR), .size = sizeof(type) * n, .deallocator = NULL }
#define managed_ptr_reset(type, ptr, mem_) if (ptr.mem) bfree(ptr.mem, ptr.size, M_MANAGED_PTR); ptr.mem = (void*) mem_; ptr.size = sizeof(type)
#define managed_ptr_reset_n(type, ptr, mem_, n) if (ptr.mem) bfree(ptr.mem, ptr.size, M_MANAGED_PTR); ptr.mem = (void*) mem_; ptr.size = sizeof(type) * n 
#define managed_ptr_mem(type, ptr) (type*)ptr.mem
#define managed_ptr(type) managed_ptr_t
#define managed_ptr_set_deallocator(ptr, dealloc) ptr.deallocator = dealloc

void managed_ptr_free(managed_ptr_t ptr);
