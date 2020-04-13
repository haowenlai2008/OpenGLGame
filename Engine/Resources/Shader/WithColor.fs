#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//in vec3 FragPos;  
//in vec3 Normal;  
//in vec2 TexCoords;
//in vec4 FragPosLightSpace;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform sampler2D shadowMap;
uniform vec3 mColor;

void main()
{
    // ambient
    vec4 texColor = vec4(mColor, 1.0);
    FragColor = texColor;
   //FragColor = texColor;
} 