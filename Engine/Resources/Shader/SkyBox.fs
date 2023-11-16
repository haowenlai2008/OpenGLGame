            #version 330 core
out vec4 FragColor;

in vec3 TexCoords;
struct Material {
    samplerCube diffuse;
    vec3 specular;    
    float shininess;
}; 
uniform samplerCube environmentMap;
uniform Material material;

void main()
{    
    vec3 envColor = texture(environmentMap, TexCoords).rgb;
    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2)); 
    FragColor = vec4(envColor, 1.0);
    //FragColor = texture(material.diffuse, TexCoords);

}