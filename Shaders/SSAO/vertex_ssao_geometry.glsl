#version 330 core
/*layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 viewPos = view * model * vec4(aPos, 1.0);
    FragPos = viewPos.xyz;
    TexCoords = aTexCoords;

    mat3 normalMatrix = transpose(inverse(mat3(view * model)));
    Normal = normalMatrix * aNormal;

    gl_Position = projection * viewPos;
}*/


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 inormal;
layout (location = 2) in vec3 tangent;
layout (location = 3) in vec3 bitan;
layout (location = 4) in vec2 texCoord;

/*layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;*/

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
