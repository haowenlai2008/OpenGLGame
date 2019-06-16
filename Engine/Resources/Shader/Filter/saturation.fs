#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float saturation;
const vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);
void main()
{
    vec4 col = texture(screenTexture, TexCoords);
    float luminance = dot(col.rgb, luminanceWeighting);
    vec3 greyScaleColor = vec3(luminance);
    FragColor = vec4(mix(greyScaleColor, col.rgb, saturation), col.w);
} 