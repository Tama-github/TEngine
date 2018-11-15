#version 330 core
out vec4 FragColor;
//out float FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{ 
    float i = texture(screenTexture, TexCoords).r;
    FragColor = vec4(i,i,i,0.0);
    //FragColor = texture2D(screenTexture, TexCoords);
    //FragColor = vec4(TexCoords.x, TexCoords.y,0,1);
    //FragColor = vec4(0.0);
}
