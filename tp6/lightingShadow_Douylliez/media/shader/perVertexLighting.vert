#version 130

in vec3 position;  // in Local coordinates
in vec3 normal;    // in Local coordinates

uniform mat4 modelviewMatrix; // Eye->Local
uniform mat3 normalMatrix;
uniform mat4 mvp;             // Projection * Eye->Local = Clip coordinates -> Local

uniform vec3 lightPosition;   // in Eye coordinates.

uniform vec3 materialDiffuse,materialSpecular;
uniform vec4 materialAmbient;

out vec4 fColor;

void main() {
  float diffuseIntensity;
  float specularIntensity=50;
  vec4 positionEye;
  vec3 L,V,N,R;

  positionEye=modelviewMatrix*vec4(position,1);

  V=-positionEye.xyz/positionEye.w;
  L=lightPosition+V;
  N=normalMatrix*normal;

  L=normalize(L);
  V=normalize(V);
  N=normalize(N);

  R=2*dot(N,L)*N-L;
  R=normalize(R);
  diffuseIntensity=max(dot(N,L),0.0);
  specularIntensity=pow(max(dot(V,R),0),50);

  fColor=vec4(diffuseIntensity*materialDiffuse+materialAmbient.xyz,materialAmbient.a);
 fColor=fColor+(vec4(materialSpecular.x,materialSpecular.y,materialSpecular.z,1)*specularIntensity);
  gl_Position=mvp*vec4(position,1);
}
