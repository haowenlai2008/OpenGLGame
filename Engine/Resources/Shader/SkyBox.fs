            #version 330 core
out vec4 FragColor;

in vec3 TexCoords;
struct Material {
    samplerCube diffuse;
    vec3 specular;    
    float shininess;
}; 
uniform Material material;

void main()
{    
    FragColor = texture(material.diffuse, TexCoords);
}