#pragma once

#include "vao.h"

typedef struct mesh_t {
    vao_t* vao;
    mat4 transform;
} mesh_t;

mesh_t* mesh_create(f32 vertices[], u32 num_vertices, u32 indices[], u32 num_indices);
void mesh_destroy(mesh_t* mesh);
void mesh_render(mesh_t* mesh);
