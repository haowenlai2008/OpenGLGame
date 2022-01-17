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
    viewWithoutTranslate[3] = vec4(0.0);
    viewWithoutTranslate[0][3] = 0.0;
    viewWithoutTranslate[1][3] = 0.0;
    viewWithoutTranslate[2][3] = 0.0;
    viewWithoutTranslate[3][3] = 0.0;
    vec4 pos = projection * viewWithoutTranslate * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}  