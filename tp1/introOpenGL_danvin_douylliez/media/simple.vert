#version 130
        
in vec3 position;
in vec4 color;
uniform float coeff;
out vec4 fColor; 
in  vec2 texCoord;
out vec2 fTexCoord;

       
void main() {
fColor=color;
    gl_Position=vec4(coeff*position,1.0);
fTexCoord=texCoord;

}
