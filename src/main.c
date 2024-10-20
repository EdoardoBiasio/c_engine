#include "mesh.h"
#include "math/vec.h"
#include "texture.h"
#include "parsers/obj_parser.h"
#include "camera.h"

void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    (void) source;
    (void) type;
    (void) id;
    (void) severity;
    (void) length;
    (void) userParam;
    fprintf(stderr, "Error: %s\n", message);
}

camera_t* camera = NULL;
void window_size_callback(GLFWwindow* window, i32 width, i32 height) {
    if (camera)
        camera_resize(camera, (f32) width / height);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    GLFWwindow * window = glfwCreateWindow(1080, 720, "window", NULL, NULL);
    if (!window) {
        bfatal("Unable to create wnd\n");
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glViewport(0, 0, 1080, 720);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        bfatal("Unable to init glew\n");
        return 1;
    }

    stbi_set_flip_vertically_on_load(true);
    i32 flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    glEnable(GL_DEPTH_TEST);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        binfo("Output enabled!");
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, NULL);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    }
    u32* indices = bmalloc(sizeof(u32) * 6, M_UNUSED);

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 1;
    indices[4] = 2;
    indices[5] = 3;

    mat4 translation = mat4_identity();
    translation = mat4_translate(translation, 0.4f, -0.5f, 0);
    translation = mat4_rotate(translation, 0.7f, 0, 0);

    test_mat4();
    managed_ptr(mesh_t) mesh = managed_ptr_empty(mesh_t);
    managed_ptr_set_deallocator(mesh, mesh_destroy);
    
    vertex_t vertices_[] = {
        (vertex_t) { (vec3) {-0.5f, 0.5f, 0.0f},   YELLOW,  (vec2) {0.0f, 1.0f}, (vec3) {0.0f, 0.0f, -1.0f} },
        (vertex_t) { (vec3) {0.5f, 0.5f, 0.0f},    RED,     (vec2) {1.0f, 1.0f}, (vec3) {0.0f, 0.0f, -1.0f} },
        (vertex_t) { (vec3) {-0.5f, -0.5f, 0.0f},  GREEN,   (vec2) {0.0f, 0.0f}, (vec3) {0.0f, 0.0f, -1.0f} },
        (vertex_t) { (vec3) {0.5f, -0.5f, 0.0f},   BLUE,    (vec2) {1.0f, 0.0f}, (vec3) {0.0f, 0.0f, -1.0f} }
    };
    managed_ptr(float) ptr = vertex_get_float_array(vertices_, 4);

    optional_p(char) file_path = get_file_path();
    if (file_path.ok != true) {
        berror(file_path.error);
        return 1;
    }


    print_memory_stats();
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera_translate(camera, (vec3) {0.0, 0.0, -0.05f});
        }
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera_translate(camera, (vec3) {0.05f, 0.0, 0.0});
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera_translate(camera, (vec3) {-0.05f, 0.0, 0.0});
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera_translate(camera, (vec3) {0.0, 0.0, 0.05f});
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            camera_translate(camera, (vec3) {0.0, 0.05f, 0.0});
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            camera_translate(camera, (vec3) {0.0, -0.05f, 0.0});
        }
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
            camera_rotate(camera, (vec3) {0.0, 0.025f, 0.0});
        } 
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
            camera_rotate(camera, (vec3) {0.0, -0.025f, 0.0});
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            camera_rotate(camera, (vec3) {0.025f, 0.0, 0.0});
        } 
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
            camera_rotate(camera, (vec3) {-0.025f, 0.0, 0.0});
        }
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        mat4 mvp = mat4_mul(camera->projection_matrix, camera->view_matrix);

        glfwSwapBuffers(window);
    }

    point_light_destroy(light);
    shader_destroy(shader);
    managed_ptr_free(mesh);
    texture_destroy(texture);
    camera_destroy(camera);
    print_memory_stats();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
