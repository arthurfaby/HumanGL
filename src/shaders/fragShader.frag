#version 450 core

in vec3 fragmentColor;// Vertex shader output

out vec3 finalColor;// Final color of the fragment

void main() {
    finalColor = vec3(fragmentColor.r, fragmentColor.g, fragmentColor.b);
}
