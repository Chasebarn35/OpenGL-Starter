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
    unsigned int vertexShader[2];
    vertexShader[0] = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader[0], 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader[0]);
    ShaderSuccess(vertexShader[0],"VERTEX");//vertex Shader Code
    vertexShader[1] = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader[1], 1, &vertexShader2Source, NULL);
    glCompileShader(vertexShader[1]);
    ShaderSuccess(vertexShader[1],"VERTEX2");//slightly moved vertex shading?

    unsigned int fragmentShader[2];
    fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader[0], 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader[0]);
    ShaderSuccess(fragmentShader[0],"FRAGMENT");

    fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader[1], 1, &fragmentShader2Source, NULL);
    glCompileShader(fragmentShader[1]);
    ShaderSuccess(fragmentShader[1],"FRAGMENT2");

    unsigned int shaderProgram[2];
    shaderProgram[0] = glCreateProgram();
    glAttachShader(shaderProgram[0], vertexShader[0]);
    glAttachShader(shaderProgram[0], fragmentShader[0]);
    glLinkProgram(shaderProgram[0]);
    LinkSuccess(shaderProgram[0],"PROGRAM");

    shaderProgram[1] = glCreateProgram();
    glAttachShader(shaderProgram[1], vertexShader[1]);
    glAttachShader(shaderProgram[1], fragmentShader[1]);
    glLinkProgram(shaderProgram[1]);
    LinkSuccess(shaderProgram[1],"PROGRAM2");

glUseProgram(shaderProgram[0]);//use shader program to render

glDeleteShader(vertexShader[0]);
glDeleteShader(vertexShader[1]);
glDeleteShader(fragmentShader[0]);
glDeleteShader(fragmentShader[1]);
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
glBindVertexArray(VAO);
glUseProgram(shaderProgram[0]);//use shader program to render
glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
glUseProgram(shaderProgram[1]);
glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);


//-----------------------------------------------------------------
    glfwSwapBuffers(window);//renders whatever is put on the window
    glfwPollEvents();//polls output?
}

glfwTerminate();
return 0;
}
