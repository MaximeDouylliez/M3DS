#version 130

uniform sampler2D  depthTexture ;

in vec4 fTexCoord;

out vec4 fragColor;

void main() {
  vec4 texCoord=fTexCoord;
texCoord.xy/=texCoord.w;

  texCoord= vec4((texCoord.x+1)/2,(texCoord.y+1)/2,(texCoord.z+1)/2,texCoord.w);
fragColor=texture(depthTexture,texCoord.st);
fragColor=1.0-clamp(6.0*(1.0-fragColor),0,1);

if(fragColor.r*texCoord.z<1)fragColor=vec4(0,0,0,1);
else fragColor=vec4(1,1,1,1);
}
