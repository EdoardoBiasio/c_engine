#include "camera.h"

camera_t* camera_create(vec3 position, vec3 rotation, f32 fov, f32 aspect_ratio, f32 near, f32 far) {

    camera_t* camera = bmalloc(sizeof(camera_t), M_CAMERA);
    camera->position = position;
    camera->rotation = rotation;
    camera->view_matrix = mat4_view_rotation(camera->position, camera->rotation);

    camera->fov = fov;
    camera->aspect_ratio = aspect_ratio;
    camera->near = near;
    camera->far = far;
    camera->projection_matrix = mat4_projection_perspective(fov, aspect_ratio, near, far);
    return camera;
}

void camera_change_fov(camera_t* camera, f32 fov) {
    camera->fov = fov;
    camera->projection_matrix = mat4_projection_perspective(camera->fov, camera->aspect_ratio, camera->near, camera->far);
}

void camera_resize(camera_t* camera, f32 aspect_ratio) {
    camera->aspect_ratio = aspect_ratio;
    camera->projection_matrix = mat4_projection_perspective(camera->fov, camera->aspect_ratio, camera->near, camera->far);
}

void camera_translate(camera_t* camera, vec3 translation) {
    camera->position.x += translation.x;
    camera->position.y += translation.y;
    camera->position.z += translation.z;
    camera->view_matrix = mat4_view_rotation(camera->position, camera->rotation);
}

void camera_rotate(camera_t* camera, vec3 rotation) {
    camera->rotation.x += rotation.x;
    camera->rotation.y += rotation.y;
    camera->rotation.z += rotation.z;
    camera->view_matrix = mat4_view_rotation(camera->position, camera->rotation);
}

void camera_destroy(camera_t* camera) {
    bfree(camera, sizeof(camera_t), M_CAMERA);
}
