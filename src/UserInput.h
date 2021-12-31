#include <ClownLib/ClownLib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

class StateMachine {
    private:
    GLfloat x,y;
    public:
    bool Wireframe;
    StateMachine();

//   ~StateMachine();//uhh, no actual data manipulation rn, doesnt actually delete anything
//    StateMachine(const StateMachine& source);//not sure I actually need a copy constructor
    bool getState();
    void changeState();
    void addX(GLfloat a);
    void addY(GLfloat b);
    GLfloat getX();
    GLfloat getY();
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, StateMachine& state);
void ShaderSuccess(GLuint type,std::string Name);
void LinkSuccess(GLuint type, std::string Name);

