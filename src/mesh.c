#include "mesh.h"

mesh_t* mesh_create(f32 vertices[], u32 num_vertices, u32 indices[], u32 num_indices) {
    mesh_t* mesh = bmalloc(sizeof(mesh_t), M_MESH);
    if (!mesh) return NULL;
    mesh->vao = vao_create(vertices, indices, num_vertices, num_indices);
    if (!mesh->vao) {
        bfree(mesh, sizeof(mesh_t), M_MESH);
        berror("Unable to create mesh.");
        return NULL;
    }
    mesh->transform = mat4_identity();

    return mesh;
}

void mesh_destroy(mesh_t* mesh) {
    bfree(mesh->vao, sizeof(vao_t), M_VAO);
    bfree(mesh, sizeof(mesh_t), M_MESH);
}

void mesh_render(mesh_t* mesh) {
    vao_render(mesh->vao);
}
