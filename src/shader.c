#include "reader.h"
#include <shader.h>
#include <stdio.h>
#include <glad/glad.h>
#include <string.h>
Shader create_program(char* vertex_path,char* fragment_path){
    Shader vertex_shader = create_shader(vertex_path, GL_VERTEX_SHADER);
    Shader fragment_shader = create_shader(fragment_path, GL_FRAGMENT_SHADER);
    
    int sucess;
    char info_log[512];
    Shader shader_program = glCreateProgram();

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

Shader create_shader( char* shader_path,int Shaderype){
    
    int sucess;
    char info_log[512];
    Shader shader = glCreateShader((GLenum) Shaderype);

    const char* shader_src = read_as_string(shader_path);
    if (shader_src == NULL){
        printf("FAILED TO LOAD FILE < %s >\n",shader_path);
        return shader;
    }
    
    glShaderSource(shader,1, &shader_src,NULL);
    glCompileShader(shader);
    glGetShaderiv(shader,GL_COMPILE_STATUS,&sucess);

    if (!sucess){
        glGetShaderInfoLog(shader,512,NULL,info_log);
        printf("haha you are such a failure your shader in < %s > failed to compile\n%s\n",shader_path,info_log);
    }
    
    return  shader;
}
void set_bool(Shader program, char* name,int value){
    glUniform1i(glGetUniformLocation(program,name),value);
}
void set_int(Shader program, char* name,int value){
    glUniform1i(glGetUniformLocation(program,name),value);
}
void set_float(Shader program, char* name,float value){
    glUniform1f(glGetUniformLocation(program,name),value);
}