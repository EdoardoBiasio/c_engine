#pragma once

#include "../math/vec.h"

typedef struct attenuation_t {
    f32 exponential, linear, constant;
} attenuation_t;

typedef struct point_light_t {
    const char* name;
    vec3 position;
    f32 diffuse_intensity, specular_intensity;
    attenuation_t attenuation;
} point_light_t;

typedef struct attenuation_location_t {
    u32 exponential, linear, constant;
} attenuation_location_t;

typedef struct point_light_location_t {
    u32 position, diffuse_intensity, specular_intensity;
    attenuation_location_t attenuation;
} point_light_location_t;

struct shader_t;

point_light_t* point_light_create(const char* name, vec3 position, f32 diffuse, f32 specular, attenuation_t attenuation);
point_light_location_t point_light_setup_uniforms(struct shader_t* shader);
void point_light_bind_uniforms(point_light_location_t location, point_light_t* light);
void point_light_destroy(point_light_t* light);
