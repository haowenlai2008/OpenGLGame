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
    if (projCoords.x < -1 || projCoords.x > 1 || projCoords.y < -1 || projCoords.y > 1)
        return 0f;
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
    if (projCoords.x < -1 || projCoords.x > 1 || projCoords.y < -1 || projCoords.y > 1)
        return 0f;
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
void main()
{
    // ambient
    vec4 texColor = texture(material.diffuse, fs_in.TexCoords);
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
    vec3 result = (ambient + (1.0f - shadow) * (diffuse + specular)) * texColor.rgb;
    FragColor = vec4(result, 1.0);
    //FragColor = texColor;
} 