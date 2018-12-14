#version 330 core

in vec3 normal;
in vec4 vPosition;
in vec3 vWeight;
out vec4 color;

uniform int nbLights;
uniform vec3 lights[128];
uniform vec3 objectColor;

void main() {
    color = vec4(vWeight, 0.f);
}

