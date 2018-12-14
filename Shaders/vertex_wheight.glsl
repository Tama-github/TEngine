#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 inormal;
layout (location = 5) in vec2 weight;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec4 vPosition;
out vec3 vWeight;

void main() {
    // Note that we read the multiplication from right to left
    gl_Position = projection * view * model * vec4(position, 1.0f);
    normal = mat3(transpose(inverse(model))) * inormal;
    vPosition = vec4(model* vec4(position,1.0));
    vWeight = vec3(weight, 0);
}
