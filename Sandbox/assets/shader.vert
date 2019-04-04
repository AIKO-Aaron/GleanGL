#version 330 core

#include "assets/transformations.glsl"

layout (location = 0) in vec3 attribVertPosition;
layout (location = 1) in vec3 attribVertColor;

out vec3 vertColor;
uniform float angle;
uniform mat4 camera = mat4(
                           1, 0, 0, 0,
                           0, 1, 0, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 1);

void main() {
    vertColor = attribVertColor;
    gl_Position = perspective(PI / 2.0, 0.1, 10) * camera * vec4(attribVertPosition, 1.0);
}
