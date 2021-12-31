#include "UserInput.h"
using std::cout;
using std::endl;

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
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);


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
//------------------------------------------------ SHADERS------------
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
    LinkSuccess(shaderProgram,"PROGRAM");

glUseProgram(shaderProgram);//use shader program to render

glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
//---------------------------------------------------


float vertices[] = {
-0.5f, 0.5f, 0.0f, //top left
-0.5f, -0.5f, 0.0f,//bottom left
0.5f, -0.5f, 0.0f,//bottom right
0.5f, 0.6f, 0.0f,//top right
0.0f, 0.9f, 0.0f//top middle
};
unsigned int indices[]{
    0,1,2,
    0,2,3,
    0,3,4

};

unsigned int VAO,VBO, EBO;
glGenVertexArrays(1,&VAO);
glGenBuffers(1,&VBO);
glGenBuffers(1,&EBO);
glBindVertexArray(VAO);
//copy verticies array in a buffer
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//set verticies pointer
glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
glEnableVertexAttribArray(0);

glBindBuffer(GL_ARRAY_BUFFER, 0); 

glBindVertexArray(0);//unbind so accidental calls dont happen

StateMachine wire;
while(!glfwWindowShouldClose(window)){


processInput(window,wire);



glClearColor(0.2f, wire.getY(), wire.getX(), 1.0f);
glClear(GL_COLOR_BUFFER_BIT);
glUseProgram(shaderProgram);//use shader program to render
glBindVertexArray(VAO);

glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);


//-----------------------------------------------------------------
    glfwSwapBuffers(window);//renders whatever is put on the window
    glfwPollEvents();//polls output?
}

glfwTerminate();
return 0;
}
