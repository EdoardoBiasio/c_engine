#include "lights.h"
#include "../shaders/shader.h"

point_light_t* point_light_create(const char* name, vec3 position, f32 diffuse, f32 specular, attenuation_t attenuation) {
    point_light_t* light = (point_light_t*) bmalloc(sizeof(point_light_t), M_LIGHT);
    light->name = name;
    light->position = position;
    light->diffuse_intensity = diffuse;
    light->specular_intensity = specular;
    light->attenuation = attenuation;
    return light;
}

point_light_location_t point_light_setup_uniforms(struct shader_t* shader) {
    point_light_location_t location;
    location.position = shader_get_uniform_location(shader, "light.position");
    location.diffuse_intensity = shader_get_uniform_location(shader, "light.diffuse_intensity");
    location.specular_intensity = shader_get_uniform_location(shader, "light.specular_intensity");
    location.attenuation.exponential = shader_get_uniform_location(shader, "light.att.exp");
    location.attenuation.linear = shader_get_uniform_location(shader, "light.att.linear");
    location.attenuation.constant = shader_get_uniform_location(shader, "light.att.constant");
    return location;
}

void point_light_bind_uniforms(point_light_location_t location, point_light_t* light) {
    shader_uniform_3f(location.position, light->position);
    shader_uniform_1f(location.diffuse_intensity, light->diffuse_intensity);
    shader_uniform_1f(location.specular_intensity, light->specular_intensity);
    shader_uniform_1f(location.attenuation.exponential, light->attenuation.exponential);
    shader_uniform_1f(location.attenuation.linear, light->attenuation.linear);
    shader_uniform_1f(location.attenuation.constant, light->attenuation.constant);
}

void point_light_destroy(point_light_t* light) {
    bfree(light, sizeof(point_light_t), M_LIGHT);
}
