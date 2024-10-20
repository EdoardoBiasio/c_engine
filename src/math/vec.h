#pragma once

#include "../includes.h"
#include "../utils/logging.h"
#include "../utils/memory.h"

f32 deg_to_rad(f32 degrees);
f32 rad_to_deg(f32 radians);

typedef struct vec2 {
    f32 x, y;
} vec2;

typedef struct vec3 {
    f32 x, y, z;
} vec3;

vec2 vec2_add(const vec2 lhs, const vec2 rhs);
vec2 vec2_invert(const vec2 src);
vec2 vec2_sub(const vec2 lhs, const vec2 rhs); 
f32 vec2_dot(vec2 lhs, vec2 rhs); 
vec3 vec2_cross(vec2 lhs, vec2 rhs);
f32 vec2_len(vec2 val);
vec2 vec2_normalized(vec2 val);

vec3 vec3_add(const vec3 lhs, const vec3 rhs);
vec3 vec3_invert(const vec3 src);
vec3 vec3_sub(const vec3 lhs, const vec3 rhs);
f32 vec3_dot(vec3 lhs, vec3 rhs);
vec3 vec3_cross(vec3 lhs, vec3 rhs);
f32 vec3_len(vec3 val);
vec3 vec3_normalized(vec3 val);
void vec3_normalize(vec3* val);

typedef struct vec4 {
    f32 x, y, z, w;
} vec4;

vec4 vec4_add(const vec4 lhs, const vec4 rhs);
vec4 vec4_invert(const vec4 src);
vec4 vec4_sub(const vec4 lhs, const vec4 rhs); 
f32 vec4_dot(vec4 lhs, vec4 rhs);
f32 vec4_len(vec4 val);
vec4 vec4_normalized(vec4 val);

typedef struct mat4 {
    f32 m00, m01, m02, m03,
        m10, m11, m12, m13,
        m20, m21, m22, m23,
        m30, m31, m32, m33;
} mat4; // yx

typedef struct mat4_raw_data {
    f32 data[16];
} mat4_raw_data;
 
mat4 mat4_sum(mat4 lhs, mat4 rhs);
mat4 mat4_sub(mat4 lhs, mat4 rhs);
mat4 mat4_mul(mat4 lhs, mat4 rhs);
vec4 mat4_mul_vec4(mat4 lhs, vec4 rhs);
mat4_raw_data mat4_get_raw_data(mat4 value);

#define FLOAT_EQUAL_FACTOR 0.005
 
b8 f_equal(f32 lhs, f32 rhs);
 
b8 mat4_equal(mat4 lhs, mat4 rhs);
b8 vec4_equal(vec4 lhs, vec4 rhs);
b8 vec3_equal(vec3 lhs, vec3 rhs);
b8 vec2_equal(vec2 lhs, vec2 rhs);
 
mat4 mat4_translate(const mat4 src, f32 x, f32 y, f32 z);
mat4 mat4_identity();
mat4 mat4_rotate(const mat4 src, f32 x, f32 y, f32 z);
mat4 mat4_scale(const mat4 src, f32 x, f32 y, f32 z);
mat4 mat4_view_look_at(const vec3 camera_position, const vec3 target, const vec3 up);
mat4 mat4_view_rotation(const vec3 camera_position, const vec3 rotation);
mat4 mat4_projection_perspective(f32 fov, f32 aspect_ratio, f32 near, f32 far);
 
void print_mat4(mat4 val);
void test_mat4();


