#include "memory.h"

typedef struct memory_stats {
    u64 allocated_size[M_NUM];
    u64 freed_size[M_NUM];
} memory_stats;

static memory_stats stats;
static const char* tags[M_NUM] = { "STRING", "MANAGED_PTR", "SHADER", "VAO", "TEXTURE", "MESH", "CAMERA", "LIGHT", "UNUSED" };

void* bmalloc(u64 size, u16 type) {
    stats.allocated_size[type] += size;
    void* data = malloc(size);
    if (!data) {
        bfatal("Unable to allocate data for type %s.", tags[type]);
        exit(EXIT_FAILURE);
    }
    return data;
}

void bfree(void* mem, u64 size, u16 type) {
    stats.freed_size[type] += size;
    free(mem);
    mem = NULL;
}

void print_memory_stats() {
#ifdef BUILD_DEBUG 
    const u64 gib = 1024 * 1024 * 1024;
    const u64 mib = 1024 * 1024;
    const u64 kib = 1024;

    for (u32 i = 0; i < M_NUM; ++i) {
        char unit[4] = "XiB";
        f32 amount_allocated = 1.0f;
        f32 amount_freed = 1.0f;
        u64 allocated = stats.allocated_size[i];
        u64 freed = stats.freed_size[i];
        if (allocated >= gib) {
            unit[0] = 'G';
            amount_allocated = allocated / (f32)gib;
            amount_freed = freed / (f32)gib;
        } else if (allocated >= mib) {
            unit[0] = 'M';
            amount_allocated = allocated / (f32)mib;
            amount_freed = freed / (f32)mib;
        } else if (allocated >= kib) {
            unit[0] = 'K';
            amount_allocated = allocated / (f32)kib;
            amount_freed = freed / (f32)kib;
        } else {
            unit[0] = 'B';
            unit[1] = '\0';
            amount_allocated = (f32)allocated;
            amount_freed = (f32) freed;
        }
        bdebug("%s: %.2f%s - %.2f%s -> %.2f%s", tags[i], amount_allocated, unit, amount_freed, unit, amount_allocated - amount_freed, unit);;
    }
    printf("\n");
#endif
}

void managed_ptr_free(managed_ptr_t ptr) {
    if (ptr.deallocator != NULL) {
        ptr.deallocator(ptr.mem);
    } else {
        bfree(ptr.mem, ptr.size, M_MANAGED_PTR);
        ptr.mem = NULL;
    }
}
