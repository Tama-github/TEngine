#version 330 core

in vec3 normal;
in vec3 vPosition;
out vec4 color;

uniform int nbLights;
//uniform vec3 lights[128];
//uniform vec3 objectColor;

void main() {
    //Error display
    vec3 spherePos = vec3(0.0f,0.0f,0.0f);
    float sphereRadius = 1.0f;
    float dist = distance(spherePos, vPosition);
    float error = (sphereRadius - dist)/sphereRadius;
    float K = 1000;
    vec3 c = vec3(error*K,0,0);
    color = vec4(c,1.0f);
}
