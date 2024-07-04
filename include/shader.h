#ifndef SHADER_H
#define SHADER_H
#define SHADER_PATH "resources/"
typedef unsigned int Shader;
Shader create_program(char*, char*);
Shader create_shader(char*, int);
void use_program(Shader);
void set_bool(Shader, char*, int);
void set_int(Shader, char*, int);
void set_float(Shader, char*, float);
#endif