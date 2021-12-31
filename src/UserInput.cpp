#include "UserInput.h"
using std::cout;
using std::endl;


StateMachine::StateMachine():Wireframe(false),x(0.3f),y(0.3f) {}

bool StateMachine::getState(){
    return Wireframe;
}
void StateMachine::changeState(){
    Wireframe=!Wireframe;
}
void StateMachine::addX(GLfloat a){
    x+=a;
}
void StateMachine::addY(GLfloat a){
    y+=a;
}
GLfloat StateMachine::getX(){
    return x;
}
GLfloat StateMachine::getY(){
    return y;
}



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
        state.addX(0.01f);
    }
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){
        state.addX(-0.01f);
    }
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS){
        state.addY(0.01f);
    }
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS){
        state.addY(-0.01f);
    }
    if(state.getState()){
        if(glfwGetKey(window,GLFW_KEY_J) == GLFW_PRESS){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            state.changeState();
        }
    }
    else{
        if(glfwGetKey(window,GLFW_KEY_J) == GLFW_RELEASE){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            state.changeState();
        }
    }


}



void framebuffer_size_callback(GLFWwindow* window, int width, int height){
glViewport(0,0,width,height);
}
