#version 330 core
layout (location = 0) in vec3 aPos;
// 法线不需要
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(aPos, 1.0f);
    TexCoords = aTexCoords;
}