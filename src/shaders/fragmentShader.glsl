#version 450 core

in vec3 fragmentColor;  // Color from the geometry shader

out vec3 finalColor;    // Final color of the fragment

void main() {
    finalColor = fragmentColor;
}
