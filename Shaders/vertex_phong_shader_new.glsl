#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 inormal;
layout (location = 2) in vec3 tangent;
layout (location = 3) in vec3 bitan;
layout (location = 4) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool hasTexture;

out vec3 normal;
out vec4 vPosition;
out vec2 tCoord;
out mat3 TBN;


void main() {
    // Note that we read the multiplication from right to left
    gl_Position = projection * view * model * vec4(position, 1.0f);
    normal = mat3(transpose(inverse(model))) * inormal;
    vec3 t = mat3(transpose(inverse(model))) * tangent;
    vec3 bt = mat3(transpose(inverse(model))) * bitan;
    vPosition = vec4(model* vec4(position,1.0));
    tCoord = texCoord;
    TBN[0] = vec3(t[0],bt[0],normal[0]);
    TBN[1] = vec3(t[1],bt[1],normal[1]);
    TBN[2] = vec3(t[2],bt[2],normal[2]);
}
