#pragma once

#include "math/vec.h"

typedef struct camera_t {
    vec3 position;
    vec3 rotation;
    mat4 view_matrix;

    f32 fov, aspect_ratio, near, far;
    mat4 projection_matrix;
} camera_t;

camera_t* camera_create(vec3 position, vec3 rotation, f32 fov, f32 aspect_ratio, f32 near, f32 far);
#define camera_create_d() camera_create((vec3) { 0.0, 0.0, 0.0 }, (vec3) { 0.0, 0.0, 0.0 })

void camera_change_fov(camera_t* camera, f32 fov);
void camera_resize(camera_t* camera, f32 aspect_ratio);
void camera_translate(camera_t* camera, vec3 translation);
void camera_rotate(camera_t* camera, vec3 rotation);
void camera_destroy(camera_t* camera);
