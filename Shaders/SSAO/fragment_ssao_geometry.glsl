#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gAlbedo;

/*in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;*/

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in mat3 TBN;

uniform vec3 objectColor;


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

void main()
{
    // store the fragment position vector in the first gbuffer texture
    gPosition = FragPos;
    // also store the per-fragment normals into the gbuffer
    gNormal = normalize(Normal);
    // and the diffuse per-fragment color
    if (isTextured == 1) {
        gAlbedo.rgb = texture(texture_diffuse1, TexCoords).rgb;
    } else {
        gAlbedo.rgb = objectColor;
    }
    //gAlbedo.rgb = vec3(0.95);
}
