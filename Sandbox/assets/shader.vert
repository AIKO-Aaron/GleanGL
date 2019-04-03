#version 330 core

layout (location = 0) in vec3 attribVertPosition;
layout (location = 1) in vec3 attribVertColor;

out vec3 vertColor;

void main() {
    vertColor = attribVertColor;
    gl_Position = vec4(attribVertPosition, 1.0);
}
