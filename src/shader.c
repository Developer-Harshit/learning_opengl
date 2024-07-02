#include "reader.h"
#include <shader.h>
#include <stdio.h>
#include <glad/glad.h>
shader_t create_program(char* vertex_path,char* fragment_path){

    shader_t vertex_shader = create_shader(vertex_path, GL_VERTEX_SHADER);
    shader_t fragment_shader = create_shader(fragment_path, GL_FRAGMENT_SHADER);
    
    int sucess;
    char info_log[512];
    shader_t shader_program = glCreateProgram();

    glAttachShader(shader_program,vertex_shader);
    glAttachShader(shader_program,fragment_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program,GL_LINK_STATUS,&sucess);

    if(!sucess){
        glGetProgramInfoLog(shader_program,512,NULL,info_log);
        printf("Failed to Link < %s > and < %s >\n%s\n",vertex_path,vertex_path,info_log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return  shader_program;
}

shader_t create_shader( char* shader_path,int shader_type){
    
    int sucess;
    char info_log[512];
    const char* shader_src = read_as_string(shader_path);
    shader_t shader = glCreateShader((GLenum) shader_type);
    
    glShaderSource(shader,1, &shader_src,NULL);
    glCompileShader(shader);
    glGetShaderiv(shader,GL_COMPILE_STATUS,&sucess);

    if (!sucess){
        glGetShaderInfoLog(shader,512,NULL,info_log);
        printf("haha you are such a failure your shader in < %s > failed to compile\n%s\n",shader_path,info_log);
    }
    
    return  shader;
}
