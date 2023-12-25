#version 330 core
out float FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
const int blurSize = 4;
void main()
{

   vec2 texelSize = 1.0 / vec2(textureSize(screenTexture, 0));
   float result = 0.0;
   for (int x = 0; x < blurSize; ++x) 
   {
      for (int y = 0; y < blurSize; ++y) 
      {
         vec2 offset = (vec2(-2.0) + vec2(float(x), float(y))) * texelSize;
         result += texture(screenTexture, TexCoords + offset).r;
      }
   }
   FragColor = result / float(blurSize * blurSize);
} 