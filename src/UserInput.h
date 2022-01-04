#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

class StateMachine {
    private:
    GLfloat x,y;
    bool state[4];//maybe change to a variable length array or vector
    public:
    StateMachine();
//   ~StateMachine();//uhh, no actual data manipulation rn, doesnt actually delete anything
//    StateMachine(const StateMachine& source);//not sure I actually need a copy constructor
    bool getState(int num) { return state[num];}
    void changeState(int num) {state[num]=!state[num];}
    void addX(GLfloat a) {x+=a;}
    void addY(GLfloat b) {y+=b;}
    GLfloat getX() { return x;}
    GLfloat getY() { return y;}
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void error_callback(int error, const char* description);
void processInput(GLFWwindow* window, StateMachine& state);
void ShaderSuccess(GLuint type,std::string Name);
void LinkSuccess(GLuint type, std::string Name);
double findFPS(double prevtime);

