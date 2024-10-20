#include "obj_parser.h"


void string_trim(char* string, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        if (string[i] == ' ') {
            if (i < len - 1) {
                for (size_t j = i; j < len - 1; ++j) {
                    string[j] = string[j + 1];
                }
                i--;
            } else {
                string[i] = '\0';
            }
        }
    }

}

#define string_array_register(string_num, string_len) struct string_array_ ## string_num ## _ ## string_len  { char elements[string_num][string_len]; size_t len; }
#define string_array_t(string_num, string_len) struct string_array_ ## string_num ## _ ## string_len 

string_array_register(20, 20);

string_array_t(20, 20) string_split(char* string, size_t len, char element) {
    size_t num_strings = 0;
    for (size_t i = 0; i < len; ++i) {
        if (string[i] == element && i != 0 && i < len - 1) num_strings++;
    }
    num_strings++;
    string_array_t(20, 20) strings = {0};
    size_t current_string = 0;
    size_t current_string_size = 0;
    for (size_t i = 0; i < len; ++i) {
        if (string[i] == element || string[i] == '\n' || string[i] == '\0') {
            if (i == 0) continue;
            if (i != len - 1 && string[i + 1] == element) continue;
            if (current_string_size == 0) continue;
            strings.elements[current_string][current_string_size] = '\0';
            current_string++;
            strings.len ++;
            current_string_size = 0;
        } else {
            strings.elements[current_string][current_string_size] = string[i];
            current_string_size++;
        }
    }
    return strings;
}

#define MAX_VERTICES 4096
f32* reorder_float_buffer(f32* buffer, size_t buffer_len, size_t buffer_stride, u32* indices) {
    f32* buffer_new = bmalloc(sizeof(f32) * buffer_len * buffer_stride, M_UNUSED);
    memset(buffer_new, 0, sizeof(f32) * buffer_len * buffer_stride);
    for (size_t i = 0; i < buffer_len; i ++) {
        for (size_t j = 0; j < buffer_stride; j++) {
            buffer_new[i * buffer_stride + j] = buffer[indices[i] * buffer_stride + j];
        }
    }

    return buffer_new;
}

void print_float_buffer(f32* buffer, size_t len, size_t stride) {
    for (size_t i = 0; i < len; ++i) {
        printf("%u: ", i);
        for (size_t j = 0; j < stride; ++j) {
            printf("%f ", buffer[i * stride + j]);
        }
        printf("\n");
        fflush(stdout);
    }
}


mesh_t* parse_file_obj(const char* file_path) {
    FILE* fp = fopen(file_path, "r");

    vec3 vertices[MAX_VERTICES];
    size_t current_vertex = 0;
    
    vec2 uvs[MAX_VERTICES];
    size_t current_uv = 0;

    vec3 normals[MAX_VERTICES];
    size_t current_normal = 0;

    u32 vertex_indices[MAX_VERTICES];
    size_t current_vertex_index = 0;
    u32 uv_indices[MAX_VERTICES];
    size_t current_uv_index = 0;
    u32 normal_indices[MAX_VERTICES];
    size_t current_normal_index = 0;

    const size_t max_line_length = 64;
    size_t line_length = max_line_length;
    char *line = bmalloc(sizeof(char) * max_line_length, M_STRING);
    while (getline(&line, &line_length, fp) != -1) {
        string_array_t(20, 20) elements = string_split(line, line_length, ' ');
        if (strcmp(elements.elements[0], "vt") == 0) {
            if (elements.len != 3) {
                berror("Unable to parse vertex uv coordinates %s, too few or too many values.", line);
                bfree(line, sizeof(char) * max_line_length, M_STRING);
                fclose(fp);
                return NULL;
            }

            uvs[current_uv].x = strtof(elements.elements[1], NULL);
            uvs[current_uv].y = strtof(elements.elements[2], NULL);
            current_uv++;
        } else if (strcmp(elements.elements[0], "vn") == 0) {
            if (elements.len != 4) {
                berror("Unable to parse vertex normal %s, too few or too many values (%d != 4).", line, elements.len);
                bfree(line, sizeof(char) * max_line_length, M_STRING);
                fclose(fp);
                return NULL;
            }

            normals[current_normal].x = strtof(elements.elements[1], NULL);
            normals[current_normal].y = strtof(elements.elements[2], NULL);
            normals[current_normal].z = strtof(elements.elements[3], NULL);
            current_normal++;
        } else if (strcmp(elements.elements[0], "v") == 0) {
            if (elements.len != 4) {
                berror("Unable to parse vertex %s, too few or too many values (%d != 4).\n%s\n%s\n%s\n%s.", line, elements.len, elements.elements[0], elements.elements[1], elements.elements[2], elements.elements[3]);
                bfree(line, sizeof(char) * max_line_length, M_STRING);
                fclose(fp);
                return NULL;
            }

            vertices[current_vertex].x = strtof(elements.elements[1], NULL);
            vertices[current_vertex].y = strtof(elements.elements[2], NULL);
            vertices[current_vertex].z = strtof(elements.elements[3], NULL);
            current_vertex++;
        } else if (strcmp(elements.elements[0], "f") == 0) {
            if (elements.len != 4) {
                berror("Unable to parse face %s, too few or too many values.", line);
                bfree(line, sizeof(char) * max_line_length, M_STRING);
                fclose(fp);
                return NULL;
            }
            string_array_t(20, 20) indices = string_split(elements.elements[1], strlen(elements.elements[1]) + 1, '/');
            vertex_indices[current_vertex_index++] = strtoul(indices.elements[0], NULL, 0) - 1;
            uv_indices[current_uv_index++] = strtoul(indices.elements[1], NULL, 0) - 1;
            normal_indices[current_normal_index++] = strtoul(indices.elements[2], NULL, 0) - 1;
            
            indices = string_split(elements.elements[2], strlen(elements.elements[2]) + 1, '/');
            vertex_indices[current_vertex_index++] = strtoul(indices.elements[0], NULL, 0) - 1;
            uv_indices[current_uv_index++] = strtoul(indices.elements[1], NULL, 0) - 1;
            normal_indices[current_normal_index++] = strtoul(indices.elements[2], NULL, 0) - 1;
            
            indices = string_split(elements.elements[3], strlen(elements.elements[3]) + 1, '/');
            vertex_indices[current_vertex_index++] = strtoul(indices.elements[0], NULL, 0) - 1;
            uv_indices[current_uv_index++] = strtoul(indices.elements[1], NULL, 0) - 1;
            normal_indices[current_normal_index++] = strtoul(indices.elements[2], NULL, 0) - 1;

        }
        memset(line, ' ', max_line_length);
    }

    bfree(line, sizeof(char) * max_line_length, M_STRING);
    fclose(fp);

    if (current_normal_index != current_uv_index || current_uv_index != current_vertex_index) {
        berror("Different sizes: normal: %u, uv: %u, vertex: %u.", current_normal_index, current_uv_index, current_vertex_index);
    }

    f32 vertices_f_array[current_vertex* 3];
    for (size_t i = 0; i < current_vertex; ++i) {
        vertices_f_array[i * 3] = vertices[i].x;
        vertices_f_array[i * 3 + 1] = vertices[i].y;
        vertices_f_array[i * 3 + 2] = vertices[i].z;
    }

    f32 uvs_f_array[current_uv * 2];
    for (size_t i = 0; i < current_uv; ++i) {
        uvs_f_array[i * 2] = uvs[i].x;
        uvs_f_array[i * 2 + 1] = uvs[i].y;
    }


    f32 normals_f_array[current_normal * 3];
    for (size_t i = 0; i < current_normal; ++i) {
        normals_f_array[i * 3] = normals[i].x;
        normals_f_array[i * 3 + 1] = normals[i].y;
        normals_f_array[i * 3 + 2] = normals[i].z;
    }

    f32* vertex_ordered = reorder_float_buffer(vertices_f_array, current_vertex_index, 3, vertex_indices);
    f32* uv_ordered = reorder_float_buffer(uvs_f_array, current_uv_index, 2, uv_indices); 
    f32* normals_ordered = reorder_float_buffer(normals_f_array, current_normal_index, 3, normal_indices); 

    vertex_t vertices_final[MAX_VERTICES] = {0};
    for (size_t i = 0; i < current_vertex_index; ++i) {
        vertices_final[i].position.x = vertex_ordered[i * 3];
        vertices_final[i].position.y = vertex_ordered[i * 3 + 1];
        vertices_final[i].position.z = vertex_ordered[i * 3 + 2];
        
        vertices_final[i].normal.x = normals_ordered[i * 3];
        vertices_final[i].normal.y = normals_ordered[i * 3 + 1];
        vertices_final[i].normal.z = normals_ordered[i * 3 + 2];
        vertices_final[i].uv.x = uv_ordered[i * 2];
        vertices_final[i].uv.y = uv_ordered[i * 2 + 1];
        vertices_final[i].color = WHITE;
    } 

    managed_ptr(f32) float_array_final = vertex_get_float_array(vertices_final, MAX_VERTICES);
    u32 indices_array_final[current_vertex_index];
    for (size_t i = 0; i < current_vertex_index; ++i) {
        indices_array_final[i] = i;
    }

    mesh_t* mesh = mesh_create(managed_ptr_mem(f32, float_array_final), current_vertex_index, indices_array_final, current_vertex_index);
    managed_ptr_free(float_array_final);
    bfree(vertex_ordered, sizeof(f32) * current_vertex_index * 3, M_UNUSED);
    bfree(uv_ordered, sizeof(f32) * current_uv_index * 2, M_UNUSED);
    bfree(normals_ordered, sizeof(f32) * current_normal_index * 3, M_UNUSED);

    return mesh;
}

void test_string_funcs() {
#ifdef BUILD_DEBUG
    char* balls = bmalloc(sizeof(char) * 20, M_STRING);
    balls[0] = ' ';
    balls[1] = 's';
    balls[2] = 'u';
    balls[3] = 's';
    balls[4] = 's';
    balls[5] = 'y';
    balls[6] = ' ';
    balls[7] = ' ';
    balls[8] = 's';
    balls[9] = 'u';
    balls[10] = 's';
    balls[11] = ' ';
    balls[12] = '\0';
    btest(strcmp(balls, " sussy  sus ") == 0, 5);

    string_trim(balls, 20);
    btest(strcmp(balls, "sussysus") == 0, 6);

    bfree(balls, sizeof(char) * 20, M_STRING);
    
    char* sussiers = bmalloc(sizeof(char) * 20, M_STRING);
    sussiers[0] = ' ';
    sussiers[1] = 's';
    sussiers[2] = 'u';
    sussiers[3] = 's';
    sussiers[4] = 's';
    sussiers[5] = 'y';
    sussiers[6] = ' ';
    sussiers[7] = ' ';
    sussiers[8] = 's';
    sussiers[9] = 'u';
    sussiers[10] = 's';
    sussiers[11] = ' ';
    sussiers[12] = 'a';
    sussiers[13] = 'b';
    sussiers[14] = 'c';
    sussiers[15] = ' ';
    sussiers[16] = '\0';

    
    string_array_t(20, 20) arr = string_split(sussiers, 20, ' ');

    btest(strcmp(arr.elements[0], "sussy") == 0 && strcmp(arr.elements[1], "sus") == 0 && strcmp(arr.elements[2], "abc") == 0, 7);

    bfree(sussiers, sizeof(char) * 20, M_STRING);    
#endif
}
