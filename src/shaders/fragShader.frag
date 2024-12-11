#version 450 core

in vec3 fragColor;      // Color from the geometry shader

out vec3 finalColor;    // Final color of the fragment

void main() {
    finalColor = vec3(fragColor.r, fragColor.g, fragColor.b);
}
