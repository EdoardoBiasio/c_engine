#include "vec.h"

f32 deg_to_rad(f32 degrees) {
    return (degrees * M_PI) / 180.0f; 
}

f32 rad_to_deg(f32 radians) {
    return (radians * 180.0f) / M_PI;
}

vec2 vec2_add(const vec2 lhs, const vec2 rhs) {
    return (vec2) { lhs.x + rhs.x, lhs.y + rhs.y };
}

vec2 vec2_invert(const vec2 src) {
    return (vec2) { -src.x, -src.y };
}

vec2 vec2_sub(const vec2 lhs, const vec2 rhs) {
    return (vec2_add(lhs, vec2_invert(rhs)));
}

f32 vec2_dot(vec2 lhs, vec2 rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

vec3 vec2_cross(vec2 lhs, vec2 rhs) {
    return (vec3) { 0, 0, lhs.x * rhs.y - lhs.y * rhs.x };
}
 
f32 vec2_len(vec2 val) {
    return sqrtf(val.x * val.x + val.y * val.y);
}
 
vec2 vec2_normalized(vec2 val) {
    f32 len = vec2_len(val);
    return (vec2) { val.x / len, val.y / len };
}

vec3 vec3_add(const vec3 lhs, const vec3 rhs) {
    return (vec3) { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

vec3 vec3_invert(const vec3 src) {
    return (vec3) { -src.x, -src.y, -src.z };
}

vec3 vec3_sub(const vec3 lhs, const vec3 rhs) {
    return (vec3_add(lhs, vec3_invert(rhs)));
}

f32 vec3_dot(vec3 lhs, vec3 rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
 
vec3 vec3_cross(vec3 lhs, vec3 rhs) {
    return (vec3) { 
        lhs.y * rhs.z - lhs.z * rhs.y, 
        lhs.z * rhs.x - lhs.x * rhs.z, 
        lhs.x * rhs.y - lhs.y * rhs.x 
    };
}
 
f32 vec3_len(vec3 val) {
    return sqrtf(val.x * val.x + val.y * val.y + val.z * val.z);
}
 
vec3 vec3_normalized(vec3 val) {
    f32 len = vec3_len(val);
    return (vec3) { val.x / len, val.y / len, val.z / len };
}
 
void vec3_normalize(vec3* val) {
    f32 len = vec3_len(*val);
    val->x /= len;
    val->y /= len;
    val->z /= len;
}

vec4 vec4_add(const vec4 lhs, const vec4 rhs) {
    return (vec4) { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w };
}

vec4 vec4_invert(const vec4 src) {
    return (vec4) { -src.x, -src.y, -src.z, -src.w };
}

vec4 vec4_sub(const vec4 lhs, const vec4 rhs) {
    return vec4_add(lhs, vec4_invert(rhs));
}


f32 vec4_dot(vec4 lhs, vec4 rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
 
f32 vec4_len(vec4 val) {
    return sqrtf(val.x * val.x + val.y * val.y + val.z * val.z + val.w * val.w);
}
 
vec4 vec4_normalized(vec4 val) {
    f32 len = vec4_len(val);
    return (vec4) { val.x / len, val.y / len, val.z / len, val.w / len };
}
 
mat4 mat4_sum(mat4 lhs, mat4 rhs) {
    return (mat4) {    lhs.m00 + rhs.m00, lhs.m01 + rhs.m01, lhs.m02 + rhs.m02, lhs.m03 + rhs.m03,
                lhs.m10 + rhs.m10, lhs.m11 + rhs.m11, lhs.m12 + rhs.m12, lhs.m13 + rhs.m13,
                lhs.m20 + rhs.m20, lhs.m21 + rhs.m21, lhs.m22 + rhs.m22, lhs.m23 + rhs.m23,
                lhs.m30 + rhs.m30, lhs.m31 + rhs.m31, lhs.m32 + rhs.m32, lhs.m33 + rhs.m33 };
}
 
mat4 mat4_sub(mat4 lhs, mat4 rhs) {
    return (mat4) {    lhs.m00 - rhs.m00, lhs.m01 - rhs.m01, lhs.m02 - rhs.m02, lhs.m03 - rhs.m03,
                lhs.m10 - rhs.m10, lhs.m11 - rhs.m11, lhs.m12 - rhs.m12, lhs.m13 - rhs.m13,
                lhs.m20 - rhs.m20, lhs.m21 - rhs.m21, lhs.m22 - rhs.m22, lhs.m23 - rhs.m23,
                lhs.m30 - rhs.m30, lhs.m31 - rhs.m31, lhs.m32 - rhs.m32, lhs.m33 - rhs.m33 };
}
 
mat4 mat4_mul(mat4 lhs, mat4 rhs) {
    return (mat4) {    vec4_dot((vec4) {lhs.m00, lhs.m01, lhs.m02, lhs.m03}, (vec4) {rhs.m00, rhs.m10, rhs.m20, rhs.m30}), vec4_dot((vec4) {lhs.m00, lhs.m01, lhs.m02, lhs.m03}, (vec4) {rhs.m01, rhs.m11, rhs.m21, rhs.m31}), vec4_dot((vec4) {lhs.m00, lhs.m01, lhs.m02, lhs.m03}, (vec4) {rhs.m02, rhs.m12, rhs.m22, rhs.m32}), vec4_dot((vec4) {lhs.m00, lhs.m01, lhs.m02, lhs.m03}, (vec4) {rhs.m03, rhs.m13, rhs.m23, rhs.m33}),
                vec4_dot((vec4) {lhs.m10, lhs.m11, lhs.m12, lhs.m13}, (vec4) {rhs.m00, rhs.m10, rhs.m20, rhs.m30}), vec4_dot((vec4) {lhs.m10, lhs.m11, lhs.m12, lhs.m13}, (vec4) {rhs.m01, rhs.m11, rhs.m21, rhs.m31}), vec4_dot((vec4) {lhs.m10, lhs.m11, lhs.m12, lhs.m13}, (vec4) {rhs.m02, rhs.m12, rhs.m22, rhs.m32}), vec4_dot((vec4) {lhs.m10, lhs.m11, lhs.m12, lhs.m13}, (vec4) {rhs.m03, rhs.m13, rhs.m23, rhs.m33}),
                vec4_dot((vec4) {lhs.m20, lhs.m21, lhs.m22, lhs.m23}, (vec4) {rhs.m00, rhs.m10, rhs.m20, rhs.m30}), vec4_dot((vec4) {lhs.m20, lhs.m21, lhs.m22, lhs.m23}, (vec4) {rhs.m01, rhs.m11, rhs.m21, rhs.m31}), vec4_dot((vec4) {lhs.m20, lhs.m21, lhs.m22, lhs.m23}, (vec4) {rhs.m02, rhs.m12, rhs.m22, rhs.m32}), vec4_dot((vec4) {lhs.m20, lhs.m21, lhs.m22, lhs.m23}, (vec4) {rhs.m03, rhs.m13, rhs.m23, rhs.m33}),
                vec4_dot((vec4) {lhs.m30, lhs.m31, lhs.m32, lhs.m33}, (vec4) {rhs.m00, rhs.m10, rhs.m20, rhs.m30}), vec4_dot((vec4) {lhs.m30, lhs.m31, lhs.m32, lhs.m33}, (vec4) {rhs.m01, rhs.m11, rhs.m21, rhs.m31}), vec4_dot((vec4) {lhs.m30, lhs.m31, lhs.m32, lhs.m33}, (vec4) {rhs.m02, rhs.m12, rhs.m22, rhs.m32}), vec4_dot((vec4) {lhs.m30, lhs.m31, lhs.m32, lhs.m33}, (vec4) {rhs.m03, rhs.m13, rhs.m23, rhs.m33}),
    };
}
 
vec4 mat4_mul_vec4(mat4 lhs, vec4 rhs) {
    return (vec4) {
         vec4_dot((vec4) {lhs.m00, lhs.m01, lhs.m02, lhs.m03}, rhs), 
         vec4_dot((vec4) {lhs.m10, lhs.m11, lhs.m12, lhs.m13}, rhs), 
         vec4_dot((vec4) {lhs.m20, lhs.m21, lhs.m22, lhs.m23}, rhs), 
         vec4_dot((vec4) {lhs.m30, lhs.m31, lhs.m32, lhs.m33}, rhs)};
}

mat4_raw_data mat4_get_raw_data(mat4 value) {
    mat4_raw_data raw_data;
    raw_data.data[0] = value.m00;
    raw_data.data[1] = value.m10;
    raw_data.data[2] = value.m20;
    raw_data.data[3] = value.m30;
    raw_data.data[4] = value.m01;
    raw_data.data[5] = value.m11;
    raw_data.data[6] = value.m21;
    raw_data.data[7] = value.m31;
    raw_data.data[8] = value.m02;
    raw_data.data[9] = value.m12;
    raw_data.data[10] = value.m22;
    raw_data.data[11] = value.m32;
    raw_data.data[12] = value.m03;
    raw_data.data[13] = value.m13;
    raw_data.data[14] = value.m23;
    raw_data.data[15] = value.m33;
    return raw_data;
}

#define FLOAT_EQUAL_FACTOR 0.005
 
b8 f_equal(f32 lhs, f32 rhs) {
    return (fabsf(lhs - rhs) <= FLOAT_EQUAL_FACTOR);
}
 
b8 mat4_equal(mat4 lhs, mat4 rhs) {
    return (f_equal(lhs.m00, rhs.m00) && f_equal(lhs.m01, rhs.m01) && f_equal(lhs.m02, rhs.m02) && f_equal(lhs.m03, rhs.m03) &&
            f_equal(lhs.m10, rhs.m10) && f_equal(lhs.m11, rhs.m11) && f_equal(lhs.m12, rhs.m12) && f_equal(lhs.m13, rhs.m13) &&
            f_equal(lhs.m20, rhs.m20) && f_equal(lhs.m21, rhs.m21) && f_equal(lhs.m22, rhs.m22) && f_equal(lhs.m23, rhs.m23) &&
            f_equal(lhs.m30, rhs.m30) && f_equal(lhs.m31, rhs.m31) && f_equal(lhs.m32, rhs.m32) && f_equal(lhs.m33, rhs.m33));
}
 
b8 vec4_equal(vec4 lhs, vec4 rhs) {
    return (f_equal(lhs.x, rhs.x) && f_equal(lhs.y, rhs.y) && f_equal(lhs.z, rhs.z) && f_equal(lhs.w, rhs.w));
}
 
b8 vec3_equal(vec3 lhs, vec3 rhs) {
    return (f_equal(lhs.x, rhs.x) && f_equal(lhs.y, rhs.y) && f_equal(lhs.z, rhs.z));
}
 
b8 vec2_equal(vec2 lhs, vec2 rhs) {
    return (f_equal(lhs.x, rhs.y) && f_equal(lhs.y, rhs.y));
}
 
mat4 mat4_translate(const mat4 src, f32 x, f32 y, f32 z) {
    mat4 trans = (mat4) {   1, 0, 0, x, 
                            0, 1, 0, y,
                            0, 0, 1, z,
                            0, 0, 0, 1 };

    return mat4_mul(trans, src);
}
 
mat4 mat4_identity() {
    return (mat4) { 1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1 };
}
 
mat4 mat4_rotate(const mat4 src, f32 x, f32 y, f32 z) {
    mat4 rotation = mat4_identity();
    if (x != 0) {
        mat4 roll = (mat4) {    1, 0, 0, 0,
                                0, cosf(x), -sinf(x), 0,
                                0, sinf(x), cosf(x), 0,
                                0, 0, 0, 1 };
        rotation = mat4_mul(roll, rotation);
    }

    if (y != 0) {
        mat4 yaw = (mat4) { cosf(y), -sinf(y), 0, 0,
                            sinf(y), cosf(y), 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1 };
        rotation = mat4_mul(yaw, rotation);
    }

    if (z != 0) {
        mat4 pitch = (mat4) {   cosf(z), 0, sinf(z), 0,
                                0, 1, 0, 0,
                                -sinf(z), 0, cosf(z), 0,
                                0, 0, 0, 1 };
        rotation = mat4_mul(pitch, rotation);
    }

    return mat4_mul(rotation, src);
}

mat4 mat4_view_look_at(const vec3 camera_position, const vec3 target, const vec3 up) {
    vec3 forward = vec3_normalized(vec3_sub(camera_position, target));
    vec3 right = vec3_normalized(vec3_cross(up, forward));
    vec3 up_c = vec3_normalized(vec3_cross(forward, right));

    mat4 orientation = {    right.x, right.y, right.z, 0,
                            up_c.x, up_c.y, up_c.z, 0,
                            forward.x, forward.y, forward.z, 1 };

    mat4 translation = mat4_translate(mat4_identity(), -camera_position.x, -camera_position.y, -camera_position.z);
    return (mat4_mul(orientation, translation));
}

mat4 mat4_view_rotation(const vec3 camera_position, const vec3 rotation) {
    f32 cos_pitch = cosf(rotation.x);
    f32 sin_pitch = sinf(rotation.x);
    f32 cos_yaw = cosf(rotation.y);
    f32 sin_yaw = sinf(rotation.y);

    vec3 xaxis = { cos_yaw, 0, -sin_yaw };
    vec3 yaxis = { sin_yaw * sin_pitch, cos_pitch, cos_yaw * sin_pitch };
    vec3 zaxis = { sin_yaw * cos_pitch, -sin_pitch, cos_pitch * cos_yaw };

    mat4 view = {
        xaxis.x, xaxis.y, xaxis.z, -vec3_dot(xaxis, camera_position),
        yaxis.x, yaxis.y, yaxis.z, -vec3_dot(yaxis, camera_position),   
        zaxis.x, zaxis.y, zaxis.z, -vec3_dot(zaxis, camera_position),
        0, 0, 0, 1
    };    

    return view;
}

mat4 mat4_projection_perspective(f32 fov, f32 aspect_ratio, f32 near, f32 far) {
    f32 frustum_length = far - near;
    f32 y_scale = (f32) ((1.0f / tanf(fov / 2.0f)) * aspect_ratio);
    f32 x_scale = y_scale / aspect_ratio;
 
    return (mat4) { x_scale,    0,          0,                                  0,
                    0,          y_scale,    0,                                  0,
                    0,          0,          -1 * (far + near) / frustum_length, -2 * far * near / frustum_length,
                    0,          0,          -1,                                 0 };
}

mat4 mat4_scale(const mat4 src, f32 x, f32 y, f32 z) {
    return (mat4) { x, 0, 0, 0,
                    0, y, 0, 0,
                    0, 0, z, 0,
                    0, 0, 0, 1 };
}
 
void print_mat4(mat4 val) {
    printf("|%.2f, %.2f, %.2f, %.2f|\n|%.2f, %.2f, %.2f, %.2f|\n|%.2f, %.2f, %.2f, %.2f|\n|%.2f, %.2f, %.2f, %.2f|\n", 
        (f64) val.m00,(f64) val.m01,(f64) val.m02,(f64) val.m03, 
        (f64) val.m10,(f64) val.m11,(f64) val.m12,(f64) val.m13, 
        (f64) val.m20,(f64) val.m21,(f64) val.m22,(f64) val.m23, 
        (f64) val.m30,(f64) val.m31,(f64) val.m32,(f64) val.m33);
}

void test_mat4() {
#ifdef BUILD_DEBUG
    mat4 a = {  5, 1, 2, 3, 
                0, 1, -1, 3,
                -2, 0, 1 ,4,
                1, 0, -1, 3 };
    mat4 b = {  1, 0, -1, 3,
                2, 1, -2, 0,
                1, -5, 4, 3,
                0, 1, -1, 2 };
    btest(mat4_equal(mat4_mul(a, b), (mat4) {9, -6, -2, 27, 1, 9, -9, 3, -1, -1, 2, 5, 0, 8, -8, 6}), 1);

    mat4 c = {  5, 1, 2, 3,
                -1, 0, 3, 6,
                1, 0, 2, 4,
                3, 1, -1, 0 }; 

    btest(vec4_equal(mat4_mul_vec4(c, (vec4) {5, 0, 1, 2}), (vec4) {33, 10, 15, 14}), 2);
    
    mat4 id = { 1, 0, 0, -1,
                0, 1, 0, 0.4,
                0, 0, 1, -2.4,
                0, 0, 0, 1 };
    btest(mat4_equal(mat4_translate(id, 0.4f, 0.2f, 0.9f), (mat4) {1.0, 0.0, 0.0, -0.6, 0.0, 1.0, 0.0, 0.6, 0.0, 0.0, 1.0, -1.5, 0.0, 0.0, 0.0, 1.0}), 3);
    
    btest(mat4_equal(mat4_rotate(mat4_identity(), M_PI / 6, 0, 0), (mat4) {1, 0, 0, 0, 0, 0.87, -0.5, 0, 0, 0.5, 0.87, 0, 0, 0, 0, 1}), 4);
#endif
}

