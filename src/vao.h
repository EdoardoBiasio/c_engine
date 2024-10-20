#pragma once

#include "math/vec.h"
#include "shaders/shader.h"
#include "color.h"
#include "utils/memory.h"

typedef struct vertex_t {
    vec3 position;
    color color;
    vec2 uv; 
    vec3 normal;
} vertex_t;

#define VERTEX_FLOAT_NUM 12

managed_ptr(float) vertex_get_float_array(vertex_t vertices[], u32 num);

typedef struct vao_t {
    GLuint ID, VBO, EBO;
    u32 vertex_num, element_num;
} vao_t;

vao_t* vao_create(f32 vertices[], u32 indices[], u32 vertices_num, u32 element_num);
void vao_render(vao_t* vao);
void vao_bind(vao_t* vao);
void vao_unbind();
void vao_destroy(void* vao);
