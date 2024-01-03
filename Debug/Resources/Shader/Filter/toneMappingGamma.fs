#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

vec3 ACESFilm(vec3 x)
{
    float a = 2.51f;
    float b = 0.03f;
    float c = 2.43f;
    float d = 0.59f;
    float e = 0.14f;
    return clamp(((x*(a*x+b))/(x*(c*x+d)+e)), 0.0, 1.0);
}

void main()
{
    float gamma = 2.2;
    float pureWhite = 1.0;
    vec4 col = texture(screenTexture, TexCoords);
    float luminance = dot(col.rgb, vec3(0.2126, 0.7152, 0.0722));
    float mappedLuminance = (luminance * (1.0 + luminance / (pureWhite * pureWhite))) / (1.0 + luminance);
    vec3 mappedColor = (mappedLuminance / luminance) * col.rgb;
    mappedColor = mix(mappedColor, ACESFilm(col.rgb * 1.15), 0.2);
    vec3 finalColor = pow(mappedColor, vec3(1.0 / gamma));
    FragColor = vec4(finalColor, col.a);
} 