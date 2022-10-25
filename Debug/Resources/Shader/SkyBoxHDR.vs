#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 localPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{
    localPos = aPos;
	mat4 viewWithoutTranslate = view;
    viewWithoutTranslate[3] = vec4(0.0);    // 去掉平移分量
    vec4 pos = projection * viewWithoutTranslate * vec4(aPos, 1.0);
	gl_Position = pos.xyww;
}