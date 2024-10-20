#pragma once

#include "../includes.h"
#include "../utils/memory.h"
#include "../math/vec.h"
#include "../utils/optional.h"
#include "../utils/file.h"
#include "../lights/lights.h"

#define CHECK_SHADER_MISMATCH(shader, _type) if (shader->type != _type) { berror("Shader type mismatch."); return; }

typedef enum shader_type_t {
    SHADER_MODEL,
    SHADER_NUM
} shader_type_t;

typedef struct shader_t {
    GLuint program, vertex, fragment;
    shader_type_t type;
    void* shader;
} shader_t;

typedef struct shader_model_t {
    u32 transform_location, samp_location, mvp_location, camera_position_location;
    point_light_location_t point_light_location;
    mat4 current_transform, current_mvp;
    vec3 camera_position;
    u32 sampler;
    point_light_t* current_light;
} shader_model_t;


shader_t* shader_create(const char* vertex_path, const char* fragment_path, shader_type_t type);
void shader_destroy(shader_t* shader);
void shader_bind(shader_t* shader);
u32 shader_get_uniform_location(shader_t* shader, const char* uniform_name);
void shader_uniform_1f(u32 location, f32 value);
void shader_uniform_3f(u32 location, vec3 value);
void shader_uniform_4f(u32 location, vec4 value);
void shader_uniform_mat4(u32 location, mat4 value);
void shader_uniform_1i(u32 location, i32 value);
void shader_bind_uniforms(shader_t* shader);
void shader_unbind();

void shader_load_model_shader(shader_t* shader, mat4 transform, mat4 mvp, u32 texture, vec3 camera_position, point_light_t* light);
void shader_setup_model_shader(shader_t* shader);
void shader_bind_model_shader(shader_t* shader);
