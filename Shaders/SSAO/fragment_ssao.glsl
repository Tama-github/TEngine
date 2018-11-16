#version 330 core
out float FragColor;
in vec2 TexCoords;

uniform int width;
uniform int height;
uniform float radius;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D texNoise;

uniform vec3 samples[64];

int kernelSize = 64;
float bias = 0.025;

vec2 noiseScale = vec2(width/4.0, height/4.0);

uniform mat4 projection;

void main() {
    vec3 fragPos = texture(gPosition, TexCoords).xyz;
    vec3 normal = normalize(texture(gNormal, TexCoords).rgb);
    vec3 randomVec = normalize(texture(texNoise, TexCoords * noiseScale).xyz);
    vec3 tangent = normalize(randomVec - normal * dot(randomVec, normal));
    vec3 bitangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, bitangent, normal);

    float occlusion = 0.0;
    for(int i = 0; i < kernelSize; i++) {
        vec3 samp = TBN * samples[i];
        samp = fragPos + samp * radius;

        vec4 offset = vec4(samp, 1.0);
        offset = projection * offset;
        offset.xyz /= offset.w;
        offset.xyz = offset.xyz * 0.5 + 0.5;

        float sampleDepth = texture(gPosition, offset.xy).z;
        float rangeCheck = smoothstep(0.0, 1.0, radius / abs(fragPos.z - sampleDepth));
        occlusion += (sampleDepth >= samp.z + bias ? 1.0 : 0.0) * rangeCheck;

    }
    occlusion = 1.0 - (occlusion / kernelSize);
    FragColor = occlusion;
}

