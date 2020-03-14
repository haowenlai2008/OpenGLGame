#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    float col = texture(screenTexture, TexCoords).r;
    FragColor = vec4(vec3(col), 1.0f);
} 