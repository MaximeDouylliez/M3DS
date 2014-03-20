#version 130

out vec4 fragColor;
in vec3 fN,fL,fV;
uniform vec3 materialDiffuse,materialSpecular;
uniform vec4 materialAmbient;

void main() {

  vec3 N,L,V,R;
N=fN;
L=fL;
V=fV;






  float diffuseIntensity;
  float specularIntensity=1;

  L=normalize(L);
  V=normalize(V);
  N=normalize(N);

  R=2*dot(N,L)*N-L;
  R=normalize(R);
  diffuseIntensity=max(dot(N,L),0.0);
  specularIntensity=pow(max(dot(V,R),0),50);

  fragColor=vec4(diffuseIntensity*materialDiffuse+materialAmbient.xyz,materialAmbient.a);
 fragColor=fragColor+(vec4(materialSpecular.x,materialSpecular.y,materialSpecular.z,1)*specularIntensity);





}
