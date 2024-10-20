#include "shader.h"

void shader_load_model_shader(shader_t* shader, mat4 transform, mat4 mvp, u32 texture, vec3 camera_position, point_light_t* light) {
    CHECK_SHADER_MISMATCH(shader, SHADER_MODEL);

    shader_model_t* model = (shader_model_t*) shader->shader;
    model->sampler = texture;
    model->current_mvp = mvp;
    model->camera_position = camera_position;
    model->current_transform = transform;
    model->current_light = light;
}

void shader_setup_model_shader(shader_t* shader) {
    CHECK_SHADER_MISMATCH(shader, SHADER_MODEL);

    shader_model_t* model = (shader_model_t*) shader->shader;
    model->samp_location = shader_get_uniform_location(shader, "samp");
    model->mvp_location = shader_get_uniform_location(shader, "mvp");
    model->camera_position_location = shader_get_uniform_location(shader, "camera_position");
    model->transform_location = shader_get_uniform_location(shader, "translation");
    model->point_light_location = point_light_setup_uniforms(shader);
}

void shader_bind_model_shader(shader_t* shader) {
    CHECK_SHADER_MISMATCH(shader, SHADER_MODEL);

    shader_model_t* model = (shader_model_t*) shader->shader;
    shader_uniform_mat4(model->transform_location, model->current_transform);
    shader_uniform_mat4(model->mvp_location, model->current_mvp);
    shader_uniform_3f(model->camera_position_location, model->camera_position);
    //bdebug("light: position: %.2f, %.2f, %.2f; diffuse: %.2f; specular: %.2f; attenuation: %.2f, %.2f, %.2f", model->current_light->position.x, model->current_light->position.y, model->current_light->position.z, model->current_light->diffuse_intensity, model->current_light->specular_intensity, model->current_light->attenuation.exponential, model->current_light->attenuation.linear, model->current_light->attenuation.constant);
    point_light_bind_uniforms(model->point_light_location, model->current_light);
    
    glBindTexture(GL_TEXTURE_2D, model->sampler);
    glActiveTexture(GL_TEXTURE0);
    shader_uniform_1i(model->samp_location, 0);
}
