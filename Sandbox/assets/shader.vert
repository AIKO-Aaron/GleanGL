#version 330 core

#include "assets/transformations.glsl"

layout (location = 0) in vec3 attribVertPosition;
layout (location = 1) in vec3 attribNormal;
layout (location = 2) in vec2 attribUV;

uniform float time;

uniform mat4 camera = mat4(
                           1, 0, 0, 0,
                           0, 1, 0, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 1);

out vec2 uv;
out vec4 normal;

void main() {
    uv = attribUV;
    normal = normalize(camera * vec4(attribNormal, 0));
    gl_Position = normal * abs(sin(time / 2)) / 2 + perspective(PI / 4.0, 0.5, 100) * camera * vec4(attribVertPosition, 1.0);
}
