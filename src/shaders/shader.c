#include "shader.h"

#define BUFFER_LOG_MAX_SIZE 512

b8 check_shader_compilation(GLuint shader, const char* name) {
    i32 success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (GL_TRUE != success) {
        char log[BUFFER_LOG_MAX_SIZE];
        glGetShaderInfoLog(shader, BUFFER_LOG_MAX_SIZE, NULL, log);
        bwarning("Error: shader %s compilation failed: %s\n", name, log);
        return false;
    }

    return true;
}

b8 check_program_link(GLuint program) {
    i32 success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (GL_TRUE != success) {
        char log[BUFFER_LOG_MAX_SIZE];
        glGetProgramInfoLog(program, BUFFER_LOG_MAX_SIZE, NULL, log);
        bwarning("Error: program linking failed: %s\n", log);
        return false;
    }

    return true;
}

b8 create_program(shader_t* shader) {
    shader->program = glCreateProgram();
    glUseProgram(shader->program);
    glAttachShader(shader->program, shader->vertex);
    glAttachShader(shader->program, shader->fragment);
    glLinkProgram(shader->program);
    if (!check_program_link(shader->program)) {
        glDeleteShader(shader->vertex);
        glDeleteShader(shader->fragment);
        glDeleteProgram(shader->program);
        bfree(shader, sizeof(shader_t), M_SHADER);
        return false;
    }

    glDeleteShader(shader->vertex);
    glDeleteShader(shader->fragment);

    shader_unbind();
    return true;
}

b8 create_type_shader(shader_t* shader) {
    switch (shader->type) {
        case SHADER_MODEL: shader->shader = bmalloc(sizeof(shader_model_t), M_SHADER); break;
        default: bwarning("Unknown shader type %u.", shader->type); return false;
    }

    return true;
}

void setup_type_shader(shader_t* shader) {
    switch (shader->type) {
        case SHADER_MODEL: shader_setup_model_shader(shader); break;
        default: bwarning("Unknown shader type %u.", shader->type); return;
    }
}

shader_t* shader_create(const char* vertex_path, const char* fragment_path, shader_type_t type) {
    optional_p(char) file_data = read_file_to_char(vertex_path);
    if (file_data.ok != true) {
        return NULL;
    }
    char* vertex_source = managed_ptr_mem(char, file_data.data);
    shader_t* shader = (shader_t*) bmalloc(sizeof(shader_t), M_SHADER);
    if (!shader) {
        return NULL;
    }
    shader->type = type;
    shader->vertex = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(shader->vertex, 1, (const GLchar* const*) &vertex_source, NULL);
    glCompileShader(shader->vertex);

    managed_ptr_free(file_data.data);
    if (!check_shader_compilation(shader->vertex, "vertex")) {
        glDeleteShader(shader->vertex);
        bfree(shader, sizeof(shader_t), M_SHADER);
        return NULL;
    }
    
    optional_p(char) fragment_data = read_file_to_char(fragment_path); 
    if (fragment_data.ok != true) {
        return NULL;
    }
    char* fragment_source = managed_ptr_mem(char, fragment_data.data);

    shader->fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(shader->fragment, 1, (const GLchar* const*) &fragment_source, NULL);
    glCompileShader(shader->fragment);

    managed_ptr_free(fragment_data.data);
    if (!check_shader_compilation(shader->fragment, "fragment")) {
        glDeleteShader(shader->vertex);
        glDeleteShader(shader->fragment);
        bfree(shader, sizeof(shader_t), M_SHADER);
        return NULL;
    }

    if (!create_program(shader)) return NULL;

    if (!create_type_shader(shader)) {
        glDeleteProgram(shader->program);
        bfree(shader, sizeof(shader_t), M_SHADER);
        return NULL;
    }

    setup_type_shader(shader);

    return shader;
}

u32 shader_get_uniform_location(shader_t* shader, const char* uniform_name) {
    return glGetUniformLocation(shader->program, uniform_name);
} 

void shader_uniform_1f(u32 location, f32 value) {
    glUniform1f(location, value);
}

void shader_uniform_3f(u32 location, vec3 value) { 
    glUniform3f(location, value.x, value.y, value.z);
}

void shader_uniform_4f(u32 location, vec4 value) {
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void shader_uniform_1i(u32 location, i32 value) {
    glUniform1i(location, value);
}

void shader_uniform_mat4(u32 location, mat4 value) {
    mat4_raw_data matrix = mat4_get_raw_data(value);
    glUniformMatrix4fv(location, 1, GL_FALSE, matrix.data);
}

void shader_bind_uniforms(shader_t* shader) {
    switch (shader->type) {
        case SHADER_MODEL: shader_bind_model_shader(shader); break;
        default: bwarning("Unknown shader type %u.", shader->type); return;
    }
}

void shader_destroy(shader_t* shader) {

    switch (shader->type) {
        case SHADER_MODEL: bfree(shader->shader, sizeof(shader_model_t), M_SHADER); break;
        default: bwarning("Unable to free shader because of unknown type %u.", shader->type); break;
    }
    glDetachShader(shader->program, shader->vertex);
    glDetachShader(shader->program, shader->fragment);
    glDeleteProgram(shader->program);
    bfree(shader, sizeof(shader_t), M_SHADER);
}

void shader_bind(shader_t* shader) {
    glUseProgram(shader->program);
}

void shader_unbind() {
    glUseProgram(0);
}
