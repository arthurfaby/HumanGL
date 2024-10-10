#version 450 core

in vec3 fragmentColor;// Correspond à la sortie du geometry shader

out vec3 finalColor;// La couleur finale à afficher

void main() {
    finalColor = fragmentColor;// Attribue la couleur reçue à la couleur finale
}
