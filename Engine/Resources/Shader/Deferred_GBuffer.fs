#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gMetallicRoughness;
layout (location = 3) out vec4 gAlbedo;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec3 TexCoords3D;
    vec4 FragPosLightSpace;
} fs_in;

struct Material {
    sampler2D diffuse;
    float metallic;
    float roughness;
    float ao;
}; 

uniform Material material;

void main()
{	
    gPosition = fs_in.FragPos;
    gNormal = fs_in.Normal;
    gMetallicRoughness = vec3(material.metallic, material.roughness, 0.0);
    gAlbedo = texture(material.diffuse, fs_in.TexCoords);
}