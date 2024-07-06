#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 Color;
out vec2 TexCoord;

void main (){
    Color = aColor;
    TexCoord = aTexCoord;
    vec3 pos = aPos;
    gl_Position = vec4(pos,1.0);
}