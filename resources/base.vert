#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform float uOffX;
uniform float uOffY;
uniform float uScale;
out vec3 Color;
void main (){
    Color = aColor;
    vec3 pos = aPos ;
    pos.x += uOffX;
    pos.y += uOffY;
    pos /= uScale;
    gl_Position = vec4(pos,1.0);
}