#version 330 core
layout (location = 0) in vec2 aPos;//坐标


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    //gl_Position = projection * view * model * vec4(aPos, 1.0);
	gl_Position = vec4(aPos, 0.0, 1.0);
}