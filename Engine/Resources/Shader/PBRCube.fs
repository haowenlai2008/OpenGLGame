#version 330 core
out vec4 FragColor;



struct Material {
    samplerCube diffuse;
    vec3 specular;    
    float shininess;
    float metallic;
    float roughness;
    float ao;
}; 

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec3 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;


uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform sampler2D shadowMap;
const float offset = 1.0 / 3200.0;
const int angleClip = 5;
const int pcfCoreSize = 5;

#define NUM_SAMPLES 10
#define BLOCKER_SEARCH_NUM_SAMPLES NUM_SAMPLES
#define PCF_NUM_SAMPLES NUM_SAMPLES
#define NUM_RINGS 10

#define EPS 1e-3
#define PI 3.141592653589793
#define PI2 6.283185307179586

vec2 poissonDisk[NUM_SAMPLES];


highp float rand_1to1(highp float x) {
  // -1 -1
  return fract(sin(x) * 10000.0);
}

highp float rand_2to1(vec2 uv) {
  // 0 - 1
  const highp float a = 12.9898, b = 78.233, c = 43758.5453;
  highp float dt = dot(uv.xy, vec2(a, b)), sn = mod(dt, PI);
  return fract(sin(sn) * c);
}

void poissonDiskSamples(const in vec2 randomSeed) {

  float ANGLE_STEP = PI2 * float(NUM_RINGS) / float(NUM_SAMPLES);
  float INV_NUM_SAMPLES = 1.0 / float(NUM_SAMPLES);

  float angle = rand_2to1(randomSeed) * PI2;
  float radius = INV_NUM_SAMPLES;
  float radiusStep = radius;

  for (int i = 0; i < NUM_SAMPLES; i++) {
    poissonDisk[i] = vec2(cos(angle), sin(angle)) * pow(radius, 0.75);
    radius += radiusStep;
    angle += ANGLE_STEP;
  }
}

void uniformDiskSamples(const in vec2 randomSeed) {

  float randNum = rand_2to1(randomSeed);
  float sampleX = rand_1to1(randNum);
  float sampleY = rand_1to1(sampleX);

  float angle = sampleX * PI2;
  float radius = sqrt(sampleY);

  for (int i = 0; i < NUM_SAMPLES; i++) {
    poissonDisk[i] = vec2(radius * cos(angle), radius * sin(angle));

    sampleX = rand_1to1(sampleY);
    sampleY = rand_1to1(sampleX);

    angle = sampleX * PI2;
    radius = sqrt(sampleY);
  }
}


float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    // 执行透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    // 变换到[0,1]的范围
    projCoords = projCoords * 0.5 + 0.5;
    float shadowTmp;
    float currentDepth = projCoords.z;
    vec2 startCoord = projCoords.xy - vec2(-1.0, 1.0) * offset * pcfCoreSize * 0.5;
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
    //float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    return shadow;
}


float ShadowCalculationRound(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    // 执行透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    // 变换到[0,1]的范围
    projCoords = projCoords * 0.5 + 0.5;
    float shadowTmp;
    float currentDepth = projCoords.z;
    // PCF
    float deltaAngle = PI2 / angleClip;
    for (int i = 0; i < angleClip; i++)
    {
        for (int j = 0; j < pcfCoreSize; j++)
        {
            vec2 tmpCoords = projCoords.xy + vec2(cos(deltaAngle * i), sin(deltaAngle * i)) * j * offset;
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
    //float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    return shadow;
}

float ShadowCalculationPoission(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    // 执行透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    // 变换到[0,1]的范围
    projCoords = projCoords * 0.5 + 0.5;

    poissonDiskSamples(projCoords.xy);
    float shadowTmp;
    float currentDepth = projCoords.z;
    for(int i = 0; i < NUM_SAMPLES; i++)
    {
        vec2 tmpCoords = poissonDisk[i];
        float x = clamp(tmpCoords.x, 0.0, 1.0);
        float y = clamp(tmpCoords.y, 0.0, 1.0);
        if (x != tmpCoords.x || y != tmpCoords.y)
           shadowTmp += 1.0;
        else
           // 检查当前片段是否在阴影中
           shadowTmp += step(texture(shadowMap, tmpCoords).r, currentDepth - 0.005);
    }
    float shadow = shadowTmp / NUM_SAMPLES;
    return shadow;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}  

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

void main()
{
    vec4 texColor = texture(material.diffuse, fs_in.TexCoords);
    //if (texColor.a < 0.1)
    //    discard;
    vec3 Lo = vec3(0.0);
    vec3 lightPos = vec3(0.0, 10, 0.0);
    vec3 N = normalize(fs_in.Normal);
    vec3 V = normalize(viewPos - fs_in.FragPos);
    vec3 L = normalize(lightPos - fs_in.FragPos);
    vec3 H = normalize(V + L);
    float distance = length(lightPos - fs_in.FragPos);
    float attenuation =  1.0/(distance * distance);
    vec3 lightColor = vec3(2.0, 2.0, 2.0);
    vec3 radiance = lightColor * attenuation;
    vec3 albedo = texColor.rgb;
    float metallic = material.metallic;
    float roughness = material.roughness;
    float ao = material.ao;
    // Fresnel
    vec3 F0 = vec3(0.04); 
    F0      = mix(F0, albedo, metallic);
    vec3 F  = fresnelSchlick(max(dot(H, V), 0.0), F0);
    // Normal
    float NDF = DistributionGGX(N, H, roughness);
    // Geometry
    float G   = GeometrySmith(N, V, L, roughness);
    vec3 nominator    = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; 
    vec3 specular     = nominator / denominator;  
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;

    float NdotL = max(dot(N, L), 0.0);        
    Lo += (kD * albedo / PI + specular) * radiance * NdotL;

    vec3 ldir = -normalize(lightPos - fs_in.FragPos);
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace, N, ldir);

    vec3 ambient = vec3(0.03) * albedo * ao;
    //vec3 color   = ambient + Lo * (1.0 - shadow);
    vec3 color   = ambient + Lo;
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));

    FragColor = vec4(color, 1.0);
} 