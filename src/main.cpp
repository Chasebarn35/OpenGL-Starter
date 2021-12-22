#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <exception>

void error_callback(int error, const char* description){
    std::cout << "Error" << error << ": " << description << std::endl;
}

int main(int argc, char* argv[]){
glfwSetErrorCallback(error_callback);
if(!glfwInit()){
    return -1;
}

GLFWwindow* window = glfwCreateWindow(640,480,"Muh Screen", NULL,NULL);

glfwMakeContextCurrent(window);



glfwTerminate();
}