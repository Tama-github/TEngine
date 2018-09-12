#version 330 core
in vec3 normal;
in vec3 vPosition;
out vec4 color;

uniform int nbLights;
uniform vec3 lights[128];
uniform vec3 objectColor;

void main() {
    color = vec4(objectColor, 1.0f);
    //vec3 l = normalize(light - v);
    vec3 l;
    float brightness = 0;
    for (int i = 0; i < nbLights; i++) {
        l = normalize(lights[i] - vPosition);
        brightness += max(-dot(normalize(normal), l), 0.0);
    }
    //float brightness = max(dot(normalize(normal), l), 0.0);
    color = color * clamp(brightness, 0, 1);
}
