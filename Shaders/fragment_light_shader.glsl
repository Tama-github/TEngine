#version 330 core

in vec3 normal;
in vec4 vPosition;
out vec4 color;

uniform int nbLights;
uniform vec3 lights[128];
uniform vec3 objectColor;

void main() {
    color = vec4(objectColor,1);
    float tmp;
    vec3 l;
    float dist;
    float b = 0;
    vec3 p = vec3(vPosition[0],vPosition[1],vPosition[2]);
    for (int i = 0; i < nbLights; i++) {
        vec3 lightPos = lights[i];
        l = normalize(lightPos - p);
        dist = distance(lightPos, p);
        float tmp = max(-dot(l, normal), 0.0);
        b += tmp/(dist);
    }
    color = color * b;
}
