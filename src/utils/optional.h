#pragma once
#include "memory.h"

typedef struct _optional {
    union {
        void* data;
        const char* error;
    };

    b8 ok;
} _optional;

typedef struct _optional_p {
    union {
        managed_ptr_t data;
        const char* error;
    };

    b8 ok;
} _optional_p;

#define optional(type) _optional
#define optional_ok(type, dat) (_optional) { .ok = true, .data = (void*) dat }
#define optional_err(type, err) (_optional) { .ok = false, .error = err }

#define optional_p(type) _optional_p
#define optional_p_ok(type, dat) (_optional_p) { .ok = true, .data = dat }
#define optional_p_err(type, err) (_optional_p) { .ok = false, .error = err }
