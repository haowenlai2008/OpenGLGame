#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
in vec4 FragPosLightSpace;

struct GBuffer {
    sampler2D pos;
    sampler2D normal;
}; 

uniform GBuffer gBuffer;
uniform sampler2D texNoise;

uniform vec2 screenSize;
uniform vec3 samples[64];
uniform mat4 projection;


void main()
{		


}