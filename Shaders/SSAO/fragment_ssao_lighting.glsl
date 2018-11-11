#version 330 core
in vec3 normal;
in vec4 vPosition;
in vec2 tCoord;
in mat3 TBN;

out vec4 color;

uniform vec3 objectColor;
uniform int nbLights;
uniform vec3 lights[128];
uniform vec3 cameraPosition;

uniform int isTextured;

struct BRDF {
    vec3 ambianteColor;
    vec3 diffuseColor;
    vec3 specularColor;
    vec3 emissiveColor;
    float opticDensity;
    int specularExp;
    float transparency;
    int lumParam;
};

BRDF brdf;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

void main() {
    vec3 p = vec3(vPosition[0],vPosition[1],vPosition[2]);
    vec3 result = vec3(0.0f,0.0f,0.0f);
    vec3 specColor;
    vec3 n;
    float b = 0.0;
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(cameraPosition - p);
    float ambientStrength = 0.1;
    float specularStrength = 0.5;
    vec3 c;

    if (isTextured == 1) {
        color = texture2D(texture_diffuse1, tCoord);
        specColor = texture2D(texture_specular1, tCoord).rgb;
        norm = normalize(texture(texture_normal1, tCoord).rgb);
        norm = normalize(norm * 2.0 - 1.0);
        norm = normalize(TBN * norm);
        c = vec3(0.0,0.0,0.0);
    } else {
        color = vec4(objectColor,1.0f);
        c = objectColor;
        specColor = vec3(1.0f,1.0f,1.0f);
        norm = normal;
    }


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

        result += (ambient + diffuse + specular) * c;
    }
    color += normalize(vec4(result, 1.0));
}
