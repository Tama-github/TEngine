#version 330 core
in vec2 TexCoords;


uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D ssao;

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


void main()
{
    vec3 lightColor = vec3(1.0,1.0,1.0);
    // retrieve data from gbuffer
    vec3 FragPos = texture2D(gPosition, TexCoords).rgb;
    vec3 Normal = texture2D(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture2D(gAlbedo, TexCoords).rgb;
    float AmbientOcclusion = texture2D(ssao, TexCoords).r;
    float constant  = 1.0; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
    float linear    = 0.09;
    float quadratic = 0.032;
    // then calculate lighting as usual
    vec3 ambient = vec3(0.3 * Diffuse * AmbientOcclusion);
    vec3 lighting  = ambient;
    vec3 viewDir  = normalize(-FragPos); // viewpos is (0.0.0)

    for (int i = 0; i < nbLights; i++) {

        // diffuse
        vec3 lightDir = normalize(lights[i] - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * lightColor;
        // specular
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), 8.0);
        vec3 specular = lightColor * spec;
        // attenuation
        float distance = length(lights[i] - FragPos);
        float attenuation = 1.0 / (1.0 + linear * distance + quadratic * distance * distance);
        diffuse *= attenuation;
        specular *= attenuation;
        lighting += diffuse + specular;
    }

    color = vec4(lighting, 1.0);
    //color = vec4(AmbientOcclusion,AmbientOcclusion,AmbientOcclusion,0.1);
}
