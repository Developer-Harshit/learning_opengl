// always include glad before including GLFW
#include "reader.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>

void framebuffer_resized(GLFWwindow* wnd, int w, int h){
    glViewport(0,0,w,h);
}

void process_input(GLFWwindow* wnd){
    if (glfwGetKey(wnd,GLFW_KEY_ESCAPE) == GLFW_PRESS ) {
        glfwSetWindowShouldClose(wnd,1); 
    }
}

int main(void){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);   // for mac os
    GLFWwindow* wnd = glfwCreateWindow(700,500,"hehe boi",NULL,NULL);

    if (wnd == NULL){
        printf("'GLFW' is a failure.It can't even create a window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(wnd);
    glfwSetFramebufferSizeCallback(wnd,framebuffer_resized);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("'GLAD' is not glad as we failed to initialize it\n");
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,700,500);
    glClearColor(0.1,0.1,0.1,1.0);

    float vertices[] = {
       -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
    };
    unsigned int indices[] = {
        0,1,2,
        3,2,0
    };


    //
    char* vertex_path = SHADER_PATH "base.vert";
    char* fragment_path = SHADER_PATH "base.frag";
    shader_t shader_program = create_program(vertex_path,fragment_path);

    // vertex
    unsigned int vao,vbo,ebo;
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    glGenBuffers(1,&ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    // position
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    // color
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    while(!glfwWindowShouldClose(wnd)){
        // do input stuff
        process_input(wnd);

        // rendering stuff
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);

        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        // glfw update stuff
        glfwSwapBuffers(wnd);
        glfwPollEvents();
    }
    glDeleteProgram(shader_program);
    glDeleteBuffers(1,&vbo);
    glDeleteBuffers(1,&ebo);
    glDeleteVertexArrays(1,&vao);
    glfwTerminate();
    return 0;
}
