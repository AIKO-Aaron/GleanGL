#define PI 3.14159265358979323

#define ASPECT (16.0f / 9.0f)

mat4 rotate_x(float angle) {
    return transpose(mat4(1, 0, 0, 0,
    0, cos(angle), sin(angle), 0,
    0, -sin(angle), cos(angle), 0,
    0, 0, 0, 1));
}

mat4 rotate_y(float angle) {
    return transpose(mat4(cos(angle), 0, sin(angle), 0,
    0, 1, 0, 0,
    -sin(angle), 0, cos(angle), 0,
    0, 0, 0, 1));
}

mat4 rotate_z(float angle) {
    return transpose(mat4(cos(angle), sin(angle), 0, 0,
    -sin(angle), cos(angle), 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1));
}

mat4 rotate(vec3 angles) {
    return (rotate_z(angles.z) * rotate_y(angles.y) * rotate_x(angles.x));
}

mat4 rotate_camera(vec3 angles) {
    return (rotate_x(angles.x) * rotate_y(angles.y) * rotate_z(angles.z));
}

mat4 translate(vec3 dir) {
    return transpose(mat4(1, 0, 0, dir.x,
    0, 1, 0, dir.y,
    0, 0, 1, dir.z,
    0, 0, 0, 1));
}

mat4 perspective(float fov_angle, float near, float far) {
    float f = 1.0f / atan(fov_angle / 2.0f);
    return transpose(mat4(f / ASPECT, 0, 0, 0,
    0, f, 0, 0,
    0, 0, -(near + far) / (near - far), 2 * near * far / (near - far),
    0, 0, 1, 0));
}

