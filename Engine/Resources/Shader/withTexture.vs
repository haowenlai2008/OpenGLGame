#version 330 core
layout (location = 0) in vec3 aPos;//坐标
layout (location = 1) in vec3 aNormal;//法线
layout (location = 2) in vec2 aTexCoord;//纹理坐标

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}