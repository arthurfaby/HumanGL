#version 450 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 12) out;

in vec3 fragmentColor[];
out vec3 fragColor;

uniform vec2 screenSize; // Taille de l’écran en pixels
const float borderWidth = 1.0; // Largeur de la bordure en pixels

void main() {
    // Convertir les positions en espace Normalized Device Coordinates (NDC)
    vec4 ndcPos[3];
    for (int i = 0; i < 3; ++i) {
        ndcPos[i] = gl_in[i].gl_Position / gl_in[i].gl_Position.w;
    }

    // Dessiner le triangle intérieur (coloré)
    for (int i = 0; i < 3; ++i) {
        gl_Position = gl_in[i].gl_Position; // Coordonnées d'origine
        fragColor = fragmentColor[i];      // Couleur d'origine
        EmitVertex();
    }
    EndPrimitive();

    // Calcul des bords et extrusion pour la bordure noire
    for (int i = 0; i < 3; ++i) {
        vec4 current = ndcPos[i];
        vec4 next = ndcPos[(i + 1) % 3];

        // Direction du bord en espace NDC
        vec2 edgeDir = normalize(next.xy - current.xy);

        // Perpendiculaire à l’edgeDir pour extrusion (90 degrés)
        vec2 perpDir = vec2(-edgeDir.y, edgeDir.x);

        // Convertir la largeur des bordures en espace NDC
        vec2 ndcBorderWidth = (borderWidth / screenSize) * 2.0;

        // Extrusion des bords pour former la bordure
        vec4 outer1 = current + vec4(perpDir * ndcBorderWidth, 0.0, 0.0);
        vec4 outer2 = next + vec4(perpDir * ndcBorderWidth, 0.0, 0.0);
        outer1.z -= 0.01; // Une petite valeur positive éloigne
        outer2.z -= 0.01;
        // Bordure noire
        gl_Position = outer1; fragColor = vec3(0.0, 0.0, 0.0); EmitVertex();
        gl_Position = outer2; fragColor = vec3(0.0, 0.0, 0.0); EmitVertex();
        gl_Position = current; fragColor = vec3(0.0, 0.0, 0.0); EmitVertex();
        gl_Position = next; fragColor = vec3(0.0, 0.0, 0.0); EmitVertex();
    }
    EndPrimitive();
}
