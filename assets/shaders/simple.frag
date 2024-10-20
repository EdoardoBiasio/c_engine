#version 330

in vec3 t_position;
in vec2 t_uv;
in vec4 t_color;
in vec3 t_normal;

out vec4 o_color;

struct attenuation {
    float exp, linear, constant;
};

struct point_light {
    vec3 position;
    float diffuse_intensity, specular_intensity;
    attenuation att;    
};


uniform point_light light;
uniform vec3 camera_position;
uniform sampler2D samp;

void main() {
    vec3 direction = t_position - light.position;
    float distance = length(direction);
    direction = normalize(direction); 
    float diffuse = max(dot(-direction, t_normal), 0.0) * light.diffuse_intensity;

    vec3 camera_to_light = normalize(light.position - camera_position);
    vec3 reflection = reflect(-camera_to_light, t_normal);
    float specular_factor = max(0.0, dot(reflection, -direction));
    specular_factor = pow(specular_factor, specular_factor) * light.specular_intensity;

    float att = distance * distance * light.att.exp + distance * light.att.linear + light.att.constant;

    o_color = texture(samp, t_uv) * t_color * (diffuse + specular_factor) / att;
}
