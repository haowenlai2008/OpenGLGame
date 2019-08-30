#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float contrast;
void main()
{
    vec4 col = texture(screenTexture, TexCoords);
    FragColor = vec4(((col.rgb - vec3(0.5)) * contrast + vec3(0.5)), col.w);
} 