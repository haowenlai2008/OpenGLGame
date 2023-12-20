#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
in vec4 FragPosLightSpace;

struct GBuffer {
    sampler2D pos;
    sampler2D normal;
    sampler2D metal_rough;
    sampler2D albedo;
    sampler2D posLightSpace;
}; 

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 color;
    float intensity;
};

uniform GBuffer gBuffer;
uniform Light light;
uniform sampler2D shadowMap;

// IBL
uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D brdfLUT;


uniform vec3 viewPos;

const float PI = 3.14159265359;

// PCF
const float offset = 1.0 / 3200.0;
const int angleClip = 5;
const int pcfCoreSize = 5;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    // 执行透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    // 变换到[0,1]的范围
    projCoords = projCoords * 0.5 + 0.5;
    float shadowTmp;
    float currentDepth = projCoords.z;
    vec2 startCoord = projCoords.xy - vec2(-1.0, 1.0) * offset * pcfCoreSize * 0.5;
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // PCF
    for (int i = 0; i < pcfCoreSize; i++)
    {
        for (int j = 0; j < pcfCoreSize; j++)
        {
            vec2 tmpCoords = startCoord + vec2(i * offset, -j * offset);
            float x = clamp(tmpCoords.x, 0.0, 1.0);
            float y = clamp(tmpCoords.y, 0.0, 1.0);
            if (x != tmpCoords.x || y != tmpCoords.y)
               shadowTmp += 1.0;
            else
               // 检查当前片段是否在阴影中
               shadowTmp += step(texture(shadowMap, tmpCoords).r, currentDepth - 0.005);
        }
    }
    float shadow = shadowTmp / (pcfCoreSize * pcfCoreSize);

    return shadow;
}


//float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
//{
//    // 执行透视除法
//    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
//    // if (projCoords.x < -1 || projCoords.x > 1 || projCoords.y < -1 || projCoords.y > 1)
//    //     return 0f;
//    // 变换到[0,1]的范围
//    projCoords = projCoords * 0.5 + 0.5;
//    float shadowTmp;
//    float currentDepth = projCoords.z;
//    float closetDepth = texture(shadowMap, projCoords.xy).r;
//    vec2 tmpCoords = projCoords.xy;
//    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
//    float x = clamp(tmpCoords.x, 0.0, 1.0);
//    float y = clamp(tmpCoords.y, 0.0, 1.0);
//    if (x != tmpCoords.x || y != tmpCoords.y)
//        shadowTmp = 0.0f;
//    else
//        // 检查当前片段是否在阴影中
//        shadowTmp = currentDepth - 0.005 > closetDepth ? 1.0 : 0.0;
//
//    float shadow = shadowTmp;
//    //float shadow = texture(shadowMap, tmpCoords).r;
//    //float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
//    return shadowTmp;
//}

// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}   
// ----------------------------------------------------------------------------
void main()
{		
    vec4 texColor = texture(gBuffer.albedo, TexCoords);
    vec3 metallRough = texture(gBuffer.metal_rough, TexCoords).rgb;
    vec4 posLightSpace = texture(gBuffer.posLightSpace, TexCoords);
    float metallic = metallRough.r;
    float roughness = metallRough.g;
    float ao = metallRough.b;
    vec3 fragPos = texture(gBuffer.pos, TexCoords).rgb;
    vec3 albedo = texColor.rgb;
    

    vec3 N = texture(gBuffer.normal, TexCoords).rgb;
    vec3 V = normalize(viewPos - fragPos);
    vec3 R = normalize(reflect(-V, N));

 
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    vec3 Lo = vec3(0.0);
    vec3 lightPos = light.position;
    vec3 lightColors = light.color;
    if (true)
    {
        // calculate per-light radiance
        vec3 L = normalize(lightPos - fragPos);
        vec3 H = normalize(V + L);
        float distance = length(lightPos - fragPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = lightColors * attenuation * light.intensity;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, roughness);   
        float G   = GeometrySmith(N, V, L, roughness);    
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);        
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
        vec3 specular = numerator / denominator;
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;	                
            
        float NdotL = max(dot(N, L), 0.0);        

        Lo += (kD * albedo / PI + specular) * radiance * NdotL; // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    }
    vec3 F = fresnelSchlickRoughness(max(dot(N, V), 0.0), F0, roughness);
    
    vec3 kS = F;
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallic;	  
    
    vec3 irradiance = texture(irradianceMap, N).rgb;
    vec3 diffuse      = irradiance * albedo;
    
    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(prefilterMap, R,  roughness * MAX_REFLECTION_LOD).rgb;
    vec2 brdf  = texture(brdfLUT, vec2(max(dot(N, V), 0.0), roughness)).rg;
    vec3 specular = prefilteredColor * (F * brdf.x + brdf.y);

    vec3 ambient = (kD * diffuse + specular) * ao;
    
    vec3 ldir = -normalize(lightPos - fragPos);
    float shadow = ShadowCalculation(posLightSpace, N, ldir);
    vec3 color   = ambient + Lo * (1.0 - shadow);
    FragColor = vec4(color, 1.0);
}