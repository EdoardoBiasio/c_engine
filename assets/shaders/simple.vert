#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 normal;

out vec3 t_position;
out vec2 t_uv;
out vec4 t_color;
out vec3 t_normal;
uniform mat4 translation;
uniform mat4 mvp;

void main() {
    t_position = vec3((translation * vec4(position, 1.0)).xyz);
    t_uv = uv;
    t_color = color;
    t_normal = normal;
    gl_Position = mvp * translation * vec4(position, 1.0);
}
