#version 330 core
in vec3 normal;
in vec4 vPosition;

out vec4 color;

uniform vec3 objectColor;
uniform int nbLights;
uniform vec3 lights[128];
uniform vec3 cameraPosition;

void main() {
    vec3 p = vec3(vPosition[0],vPosition[1],vPosition[2]);
    vec3 result = vec3(0.0,0.0,0.0);
    float b = 0.0;
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(cameraPosition - p);
    float ambientStrength = 0.1;
    float specularStrength = 0.5;

    for (int i = 0; i < nbLights; i++) {
        // ambient
        vec3 ambient = ambientStrength * vec3(1.0,1.0,1.0);//lightColor[i]

        // diffuse
        vec3 lightDir = normalize(lights[i] - p);
        float diff = max(-dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * vec3(1.0,1.0,1.0);

        // specular
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * vec3(1.0,1.0,1.0);//lightColor[i]

        result += (ambient + diffuse + specular) * objectColor;
    }
    color = vec4(result, 1.0);
}
