#version 450 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;

out vec3 fragmentColor;     // Output to fragment shader

uniform mat4 projection;    // Projection matrix

void main(void) {
    fragmentColor = vertexColor;
    gl_Position = projection * vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1);
}
