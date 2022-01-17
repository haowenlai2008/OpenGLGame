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
const float offset = 1.0 / 800.0;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    // 执行透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    
    // 变换到[0,1]的范围
    projCoords = projCoords * 0.5 + 0.5;

    // PCF
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
    );
    float shadowTmp;
    float currentDepth = projCoords.z;
    for(int i = 0; i < 9; i++)
    {
        vec2 tmpCoords = projCoords.xy + offsets[i];
        float x = clamp(tmpCoords.x, 0.0, 1.0);
        float y = clamp(tmpCoords.y, 0.0, 1.0);
        if (x != tmpCoords.x || y != tmpCoords.y)
           shadowTmp = shadowTmp + 1.0;
        else
           // 检查当前片段是否在阴影中
           shadowTmp = shadowTmp + step(texture(shadowMap, tmpCoords).r, currentDepth - 0.005);
    }
    float shadow = shadowTmp * 0.1111111111;
    //float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    return shadow;
}

void main()
{
    // ambient
    vec4 texColor = vec4(mColor, 1.0);
    if (texColor.a < 0.1)
        discard;
    vec3 ambient = light.ambient * texColor.rgb;
    vec3 lightColor = vec3(1.0);
    // diffuse 
    vec3 norm = normalize(fs_in.Normal);
    //vec3 lightDir = normalize(light.position - fs_in.FragPos);
    vec3 lightDir = -normalize(vec3(0.0f, -1.0f, 1.0f));
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * lightColor;  
    
    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular) * lightColor;  
      
    vec3 ldir = -normalize(vec3(0.0f, -1.0f, 1.0f));
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace, norm, ldir);
    shadow = 0.0f;
    vec3 result = (ambient + (1.0f - shadow) * (diffuse + specular)) * texColor.rgb;
    //result = specular * texColor.rgb;
    FragColor = vec4(result, 1.0);
   //FragColor = texColor;
} 