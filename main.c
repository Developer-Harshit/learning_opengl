// always include glad before including GLFW
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_resized(GLFWwindow* wnd , int w , int h){
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

    GLFWwindow* wnd = glfwCreateWindow(700,500,"hehe boi",NULL ,NULL);

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
    glClearColor(0.3,0.9,0.6,1.0);

    // initilize stuffs
    const char* vertex_shader_src =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main (){\n"
    "   gl_Position = vec4(aPos,1.0);\n"
    "}";
    const char* fragment_shader_src =
    "#version 330 core\n"
    "out vec4 FragColor;"
    "void main (){\n"
    "   FragColor = vec4(0.9,1.0,0.5,1.0);\n"
    "}";
    float vertices[] = {
       -0.5f ,  0.5f , 0.0f ,
        0.5f ,  0.5f , 0.0f ,
        0.5f , -0.5f , 0.0f ,
       -0.5f , -0.5f , 0.0f ,
    };
    unsigned int indices[] = {
        0,1,2,
        3,2,0
    };

    int sucess;
    char infoLog[512];
    // vertex shader
    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader,1 , &vertex_shader_src,NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader,GL_COMPILE_STATUS,&sucess);
    if (!sucess){
        glGetShaderInfoLog(vertex_shader,512,NULL,infoLog);
        printf("haha you are such a failure your vertex shader fails too.\n%s\n",infoLog);
    }

    // fragment shader
    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader,1 , &fragment_shader_src,NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader,GL_COMPILE_STATUS,&sucess);
    if (!sucess){
        glGetShaderInfoLog(fragment_shader,512,NULL,infoLog);
        printf("who the fuck fails to compile a fragment shader? shame of you.\n%s\n",infoLog);
    }

    // shader program
    unsigned int shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program,vertex_shader);
    glAttachShader(shader_program,fragment_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program,GL_LINK_STATUS,&sucess);
    if(!sucess){
        glGetProgramInfoLog(shader_program,512,NULL,infoLog);
        printf("YOU EVEN FAILED TO LINK THE DAMN SHADER PROGRAM? YOU ARE HOPELESS!.\n%s\n",infoLog);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

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
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

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

    glfwTerminate();
    return 0;
}
