#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <exception>

void error_callback(int error, const char* description){
    std::cout << "Error " << error << " { " << description << " }" << std::endl;
}

int main(int argc, char* argv[]){
glfwSetErrorCallback(error_callback);

std::cout << "helloworld" << std::endl;
if(!glfwInit()){
    return -1;
}
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);//lowest opengl version, not actually sure if this is right for what my GLAD is
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);


std::cout << "helloworld" << std::endl;

GLFWwindow* window = glfwCreateWindow(640,480,"Title", NULL,NULL);

glfwMakeContextCurrent(window);
gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

while(1){



    glfwSwapBuffers(window);//renders whatever is put on the window
    glfwPollEvents();//polls output
}

glfwTerminate();
}