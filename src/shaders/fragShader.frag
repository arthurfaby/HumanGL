#version 450 core

layout (location = 0) in vec3 fragColor; // Couleur du geometry shader
layout (location = 0) out vec4 finalColor; // Couleur finale

void main() {
    finalColor = vec4(fragColor, 1.0);
}
