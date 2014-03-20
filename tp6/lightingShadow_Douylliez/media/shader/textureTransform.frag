#version 130

uniform sampler2D image1;

in vec4 fTexCoord;

out vec4 fragColor;

void main() {
  vec4 texCoord=fTexCoord;
texCoord.xy/=texCoord.w;

  texCoord= vec4((texCoord.x+1)/2,(texCoord.y+1)/2,texCoord.z,texCoord.w);
fragColor=texture(image1,texCoord.st);
}
