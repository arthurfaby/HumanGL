#version 450 core

//layout (location = 0) in vec3 fragColor; // Couleur du geometry shader
//layout (location = 0) out vec4 finalColor; // Couleur finale
in vec3 fragmentColor;  // Vertex shader output

out vec3 finalColor;    // Final color of the fragment

void main() {
    finalColor = vec3(fragmentColor.r, fragmentColor.g, fragmentColor.b);
}
