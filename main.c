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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("'GLAD' is not glad as we failed to initialize it\n");
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,700,500);
    glfwSetFramebufferSizeCallback(wnd,framebuffer_resized);

    glClearColor(0.3,0.9,0.6,1.0);
    while(!glfwWindowShouldClose(wnd)){
        // do input stuff
        process_input(wnd);

        // rendering stuff
        glClear(GL_COLOR_BUFFER_BIT);


        // glfw update stuff
        glfwSwapBuffers(wnd);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
