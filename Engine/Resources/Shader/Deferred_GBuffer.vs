#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT {
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec3 TexCoords3D;
	vec4 FragPosLightSpace;
	vec3 ViewPos;
	vec3 ViewNormal;
}vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{
	vec4 viewPos = view * model * vec4(aPos, 1.0f);
	gl_Position = projection * viewPos;
	vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;  
    vs_out.TexCoords = aTexCoords;
	vs_out.TexCoords3D = normalize(aPos);
	vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
	vs_out.ViewPos = viewPos.xyz;
	vs_out.ViewNormal = mat3(transpose(inverse(view * model))) * aNormal;  
}