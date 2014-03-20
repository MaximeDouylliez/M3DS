#version 130

uniform sampler2D  depthTexture ;

in vec4 fTexCoord;

out vec4 fragColor;

void main() {
  vec4 texCoord=fTexCoord;
texCoord.xy/=texCoord.w;

  texCoord= vec4((texCoord.x+1)/2,(texCoord.y+1)/2,1,texCoord.w);
fragColor=texture(depthTexture,texCoord.st);
//fragColor=1.0-clamp(50.0*(1.0-fragColor),0,1);
}
