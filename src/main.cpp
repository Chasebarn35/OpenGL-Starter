#include <ClownLib/ClownLib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using std::cout;
using std::endl;

const char *vertexShaderSource = "#version 400 compatibility\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";


const char *fragmentShaderSource = "#version 400 compatibility\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, GLfloat& _X, GLfloat& _Y);
void ShaderSuccess(GLuint type,std::string Name);

int main(int argc, char* argv[]){
glfwSetErrorCallback(error_callback);

size_t windowWidth = 640;
size_t windowHeight = 480;

if(!glfwInit()){
    cout << "GLFW Failed to Initialize" << endl;
    return -1;
}
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);//GLAD version, 4.0
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


GLFWwindow* window = glfwCreateWindow(windowWidth,windowHeight,"Title", NULL,NULL);
if(!window){
    cout << "GLFW Window Failed to Open" << endl;    
    glfwTerminate();
    return -1;
}


glfwMakeContextCurrent(window);

if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    cout << "GLAD Failed to Initialize" << endl;
    return -1;
}

glViewport(0,0,windowWidth,windowHeight);
glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
GLfloat _X = .3f;
GLfloat _Y = .3f;

float vertices[] = {
-0.5f, -0.5f, 0.0f,
0.5f, -0.5f, 0.0f,
0.0f, 0.5f, 0.0f
};

unsigned int VAO,VBO;
glGenVertexArrays(1,&VAO);
glGenBuffers(1,&VBO);

glBindVertexArray(VAO);


//copy verticies array in a buffer
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    ShaderSuccess(vertexShader,"VERTEX");//vertex Shader Code

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    ShaderSuccess(fragmentShader,"FRAGMENT");

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

//TODO CHECK
glUseProgram(shaderProgram);//use shader program to render

glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);

//set verticies pointer
glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
glEnableVertexAttribArray(0);








while(!glfwWindowShouldClose(window)){
processInput(window,_X,_Y);



glClearColor(0.2f, _Y, _X, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);

glUseProgram(shaderProgram);//use shader program to render
glBindVertexArray(VAO);
glDrawArrays(GL_TRIANGLES,0,3);

    glfwSwapBuffers(window);//renders whatever is put on the window
    glfwPollEvents();//polls output
}

glfwTerminate();
return 0;
}





void ShaderSuccess(GLuint type,std::string Name){
    int success;
    char infoLog[512];//arbitrary size based off of tutorial
    glGetShaderiv(type,GL_COMPILE_STATUS,&success);
    if(!success){
    glGetShaderInfoLog(type,512,NULL,infoLog);
    cout << "ERROR::SHADER::" << Name << "::FAILURE\n" << infoLog << endl;
    }
}

void processInput(GLFWwindow* window, GLfloat& _X, GLfloat& _Y){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS){
        _X+=0.01f;
    }
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){
        _X-=0.01f;
    }
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS){
        _Y+=0.01f;
    }
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS){
        _Y-=0.01f;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
glViewport(0,0,width,height);
}
