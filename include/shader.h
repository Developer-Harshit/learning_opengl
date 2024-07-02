#ifndef SHADER_H
#define SHADER_H
#define SHADER_PATH "resources/"
typedef unsigned int shader_t;
shader_t create_program(char*, char*);
shader_t create_shader(char*, int);
void use_program(shader_t);
void set_bool(shader_t, int);
void set_int(shader_t, int);
void set_float(shader_t, float);

#endif