#version 330 core
layout (location = 0) out vec4 gPositionDepth;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gMetallicRoughness;
layout (location = 3) out vec4 gAlbedo;
layout (location = 4) out vec4 gLightSpace;
layout (location = 5) out vec4 gViewPos;
layout (location = 6) out vec3 gViewNormal;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec3 TexCoords3D;
    vec4 FragPosLightSpace;
    vec3 ViewPos;
    vec3 ViewNormal;
} fs_in;

struct Material {
    sampler2D diffuse;
    float metallic;
    float roughness;
    float ao;
}; 

uniform Material material;
uniform float near; // 投影矩阵的近平面
uniform float far;  // 投影矩阵的远平面

// 获得线性空间深度
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // 回到NDC
    return (2.0 * near * far) / (far + near - z * (far - near));    
}

void main()
{	
    gPositionDepth = vec4(fs_in.FragPos, 0);
    gNormal = fs_in.Normal;
    gMetallicRoughness = vec3(material.metallic, material.roughness, 1.0);
    gAlbedo = texture(material.diffuse, fs_in.TexCoords);
    gLightSpace = fs_in.FragPosLightSpace;
    gViewPos.xyz = fs_in.ViewPos;
    gViewPos.a = LinearizeDepth(gl_FragCoord.z);
    gViewNormal = normalize(fs_in.ViewNormal);
}