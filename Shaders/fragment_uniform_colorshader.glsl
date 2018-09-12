#version 330 core
in vec3 normal;
in vec3 vPosition;
out vec4 color;
void main() {
    //Uniform color
    color = vec4(normalize(normal)*0.5+0.5, 1.0);
}
