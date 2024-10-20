#include "vao.h"

managed_ptr(float) vertex_get_float_array(vertex_t vertices[], u32 num) {
    managed_ptr(float) float_ptr = managed_ptr_new_n(float, num * VERTEX_FLOAT_NUM);
    u32 j = 0;
    float* pp = managed_ptr_mem(float, float_ptr);
    for (u32 i = 0; i < num; ++i) {
        pp[j++] = vertices[i].position.x;
        pp[j++] = vertices[i].position.y;
        pp[j++] = vertices[i].position.z;
        pp[j++] = vertices[i].color.r;
        pp[j++] = vertices[i].color.g;
        pp[j++] = vertices[i].color.b;
        pp[j++] = vertices[i].color.a;
        pp[j++] = vertices[i].uv.x;
        pp[j++] = vertices[i].uv.y;
        pp[j++] = vertices[i].normal.x;
        pp[j++] = vertices[i].normal.y;
        pp[j++] = vertices[i].normal.z;
    }

    return float_ptr; 
}

vao_t* vao_create(f32 vertices[], u32 indices[], u32 vertices_num, u32 element_num) {
    vao_t* vao = bmalloc(sizeof(vao_t), M_VAO);

    glGenVertexArrays(1, &vao->ID);
    glBindVertexArray(vao->ID);

    vao->vertex_num = vertices_num;
    vao->element_num = element_num;
    glGenBuffers(1, &vao->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, vao->VBO);
    glBufferData(GL_ARRAY_BUFFER, vao->vertex_num * sizeof(f32) * VERTEX_FLOAT_NUM, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &vao->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vao->element_num * sizeof(u32), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_FLOAT_NUM * sizeof(f32), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_FLOAT_NUM * sizeof(f32), (const void*) (3 * sizeof(f32)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VERTEX_FLOAT_NUM * sizeof(f32), (const void*) (7 * sizeof(f32)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, VERTEX_FLOAT_NUM * sizeof(f32), (const void*) (9 * sizeof(f32)));
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    vao_unbind();

    return vao;
}

void vao_render(vao_t* vao) {
    vao_bind(vao);
    glDrawElements(GL_TRIANGLES, vao->element_num, GL_UNSIGNED_INT, NULL);
    vao_unbind();
}

void vao_bind(vao_t* vao) {
    glBindVertexArray(vao->ID);
}

void vao_unbind() {
    glBindVertexArray(0);
}

void vao_destroy(void* v) {
    vao_t* vao = (vao_t*) v;
    glDeleteVertexArrays(1, &vao->ID);
    glDeleteBuffers(1, &vao->VBO);
    glDeleteBuffers(1, &vao->EBO);
    bfree(vao, sizeof(vao_t), M_VAO);
}
