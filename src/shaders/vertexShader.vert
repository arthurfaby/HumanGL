#version 450 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;

out vec3 fragmentColor;// Output to fragment shader

void main(void) {
    fragmentColor = vertexColor;
    gl_Position = vec4(vertexPosition, 1);
}
