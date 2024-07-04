#version 330 core

uniform sampler2D uTexture0;

in vec3 Color;
in vec2 TexCoord;
out vec4 FragColor;

void main (){
    FragColor = texture(uTexture0,TexCoord) * vec4(Color,1.0);
}