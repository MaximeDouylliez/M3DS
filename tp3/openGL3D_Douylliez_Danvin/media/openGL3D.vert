#version 130
in vec3 position;
in vec3 normal;
out vec3 fColor;
uniform mat4 projection;
uniform mat4 transform;
uniform  vec3 lightPosition;
uniform vec3 diffuseColor;
void main() {
    vec3 n=normalize(normal);

    vec4 clipPosition=vec4(position,1); // coordonnées homogènes
       clipPosition=transform*clipPosition;
    clipPosition=projection*clipPosition; // transformation par la matrice de projection
     vec3 l=normalize(clipPosition.xyz/clipPosition.w-lightPosition-position);

float intensity = max(dot(n,l),0.0);
    fColor= intensity*diffuseColor;
    gl_Position=clipPosition; // gl_Position = clip coordinates

}
