#version 130

in vec4 fColor;
out vec4 fragColor;
in vec2 fTexCoord;
uniform sampler2D texture;
uniform float coeff;
void main() {

  fragColor=texture2D(texture,fTexCoord)*fColor.b;
  fragColor.g*=(1.0-coeff);
}
