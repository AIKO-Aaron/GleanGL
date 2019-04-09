#version 330 core

#include "assets/transformations.glsl"

layout (location = 0) in vec3 attribVertPosition;
layout (location = 1) in vec3 attribVertColor;
layout (location = 2) in vec3 attribNormal;

out vec3 vertColor;
uniform mat4 camera = mat4(
                           1, 0, 0, 0,
                           0, 1, 0, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 1);

out vec4 normal;

void main() {
    vertColor = attribVertColor;
    normal = camera * vec4(attribNormal, 0);
    gl_Position = normalize(normal) * 0.1 + perspective(PI / 4.0, 0.1, 100) * camera * vec4(attribVertPosition, 1.0);
}
