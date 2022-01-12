#include "UserInput.h"
using std::cout;
using std::endl;


StateMachine::StateMachine():state{(false),(false),(false),(false)},x(0.0f),y(0.3f) {}


void LinkSuccess(GLuint type, std::string Name){
    int success;
    char infoLog[512];
    glGetProgramiv(type,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(type,512,NULL,infoLog);
        cout << "ERROR::SHADER::" << Name << "::LINKING_FAILURE\n" << infoLog << endl;
    }
}

void ShaderSuccess(GLuint type,std::string Name){
    int success;
    char infoLog[512];//arbitrary size based off of tutorial
    glGetShaderiv(type,GL_COMPILE_STATUS,&success);
    if(!success){
       glGetShaderInfoLog(type,512,NULL,infoLog);
        cout << "ERROR::SHADER::" << Name << "::COMPILATION_FAILURE\n" << infoLog << endl;
    }
}


void processInput(GLFWwindow* window,StateMachine& state){//very badly written omegalul
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS){
        state.addX(0.05f);
    }
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){
        state.addX(-0.05f);
    }
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS){
        state.addY(0.05f);
    }
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS){
        state.addY(-0.05f);
    }
    if(state.getState(0)){
        if(glfwGetKey(window,GLFW_KEY_J) == GLFW_PRESS){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            state.changeState(0);
        }
    }
    else{
        if(glfwGetKey(window,GLFW_KEY_J) == GLFW_RELEASE){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            state.changeState(0);
        }
    }


}



void framebuffer_size_callback(GLFWwindow* window, int width, int height){
glViewport(0,0,width,height);
}

double findFPS(double prevtime){
    double currtime = glfwGetTime();
    cout << (int)(1/(currtime - prevtime)) << "\n";
    return currtime;
}

void error_callback(int error, const char* description){
    std::cout << "Error " << error << " { " << description << " }" << std::endl;
}
