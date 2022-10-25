#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{
    TexCoords = aPos;
    mat4 viewWithoutTranslate = view;
    viewWithoutTranslate[3] = vec4(0.0);    // 去掉平移分量
    vec4 pos = projection * viewWithoutTranslate * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}  