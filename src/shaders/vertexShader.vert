#version 450 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;

layout (location = 0) out vec3 fragmentColor; // Output to geometry shader

void main(void) {
    fragmentColor = vertexColor;
    gl_Position = vec4(vertexPosition, 1.0);
}
