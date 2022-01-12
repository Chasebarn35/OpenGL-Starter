#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::cout;
using std::endl;

int main(int argc, char* argv[]){
glfwSetErrorCallback(error_callback);

size_t windowWidth = 800;
size_t windowHeight = 600;

if(!glfwInit()){
    cout << "GLFW Failed to Initialize" << endl;
    return -1;
}
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);//GLAD version, 4.0
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


GLFWwindow* window = glfwCreateWindow(windowWidth,windowHeight,"Clown Program", NULL,NULL);
if(!window){
    cout << "GLFW Window Failed to Open" << endl;    
    glfwTerminate();
    return -1;
}

glfwMakeContextCurrent(window);
//glfwSwapInterval(0);//the vsync option, turn on if you want to not have a reduced framerate
if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    cout << "GLAD Failed to Initialize" << endl;
    return -1;
}

glViewport(0,0,windowWidth,windowHeight);
glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
//---------------------------SHADER INITIALIZATION-----------------------

Shader Shade("resources/Shaders/vertexShader.glsl","resources/Shaders/visibilityFragShader.glsl");//probably the wrong directories lol
Shader Shade2("resources/Shaders/vertexShader2.glsl","resources/Shaders/fragmentShader2.glsl");

Shade.use();



//-----------------------------------------------------------------------


float vertices[] = {
0.24f, -0.5f, 0.0f, 0.84f, 0.39f, 0.78f, 0.26f, 1.0f, 
-0.5f, -0.5f, 0.0f, 0.8f, 0.91f, 0.2f, 1.0f, 1.0f, 
-0.5f, -0.23f, 0.0f, 0.34f, 0.77f, 0.28f, 1.0f, 0.73f, 
0.18f, -0.32f, 0.0f, 0.55f, 0.48f, 0.63f, 0.32f, 0.82f, 
0.11f, -0.32f, 0.0f, 0.36f, 0.51f, 0.95f, 0.39f, 0.82f, 
0.22f, -0.26f, 0.0f, 0.92f, 0.64f, 0.72f, 0.28f, 0.76f, 
0.12f, -0.26f, 0.0f, 0.14f, 0.61f, 0.016f, 0.38f, 0.76f, 
-0.062f, -0.19f, 0.0f, 0.24f, 0.14f, 0.8f, 0.56f, 0.69f, 
0.17f, -0.16f, 0.0f, 0.16f, 0.4f, 0.13f, 0.33f, 0.66f, 
0.29f, -0.18f, 0.0f, 0.11f, 1.0f, 0.22f, 0.21f, 0.68f, 
0.31f, -0.082f, 0.0f, 0.51f, 0.84f, 0.61f, 0.19f, 0.58f, 
0.23f, -0.087f, 0.0f, 0.3f, 0.64f, 0.52f, 0.27f, 0.59f, 
0.0013f, -0.029f, 0.0f, 0.49f, 0.97f, 0.29f, 0.5f, 0.53f, 
0.3f, -0.0039f, 0.0f, 0.77f, 0.53f, 0.77f, 0.2f, 0.5f, 
0.22f, -0.0039f, 0.0f, 0.4f, 0.89f, 0.28f, 0.28f, 0.5f, 
-0.18f, 0.16f, 0.0f, 0.35f, 0.81f, 0.92f, 0.68f, 0.34f, 
-0.043f, 0.28f, 0.0f, 0.07f, 0.95f, 0.53f, 0.54f, 0.22f, 
0.092f, 0.3f, 0.0f, 0.086f, 0.19f, 0.66f, 0.41f, 0.2f, 
0.23f, 0.29f, 0.0f, 0.89f, 0.35f, 0.064f, 0.27f, 0.21f, 
0.16f, 0.46f, 0.0f, 0.02f, 0.46f, 0.063f, 0.34f, 0.042f, 
-0.27f, 0.48f, 0.0f, 0.24f, 0.97f, 0.9f, 0.77f, 0.023f, 
0.38f, 0.31f, 0.0f, 0.85f, 0.27f, 0.54f, 0.12f, 0.19f,
};

unsigned int indices[]{
0,1,2,
0,4,2,
4,7,2,
2,7,15,
7,12,15,
4,6,7,
4,3,5,
4,6,5,
6,7,12,
12,8,6,
6,5,8,
8,9,10,
10,8,11,
11,8,12,
12,11,14,
14,11,10,
10,13,14,
13,14,18,
18,14,17,
17,14,12,
17,16,12,
17,18,19,
16,15,12,
15,16,20,
16,17,20,
17,19,20,
2,15,20,
19,18,21,
13,18,21
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

//position attribute
glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 8 * sizeof(float),(void*)0);
glEnableVertexAttribArray(0);
//color attribute
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1); 
//texture attribute
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
glEnableVertexAttribArray(2);

//---------------------------TEXTURE INITIALIZATION----------------------



unsigned int texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
//I dont know what this stuff means lol
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

int x, y, n;
//stbi_set_flip_vertically_on_load(true);
unsigned char *data = stbi_load("resources/Textures/furrytexture.png", &x, &y, &n, 0);
if(data){
    glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
}
else{
    cout << "failed to load texture" << endl;
}


stbi_image_free(data);//free the image memory


//-----------------------------------------------------------------------
StateMachine wire;
double currtime = glfwGetTime();
double prevtime = currtime;
double delta = 0;
double fpsLimit = 1.0/60.0;



//---
int vertexTriangleColor = glGetUniformLocation(Shade2.ID, "ourColor");
int vertexTriangleRotation = glGetUniformLocation(Shade.ID, "rotation");

glm::mat4 trans = glm::mat4(1.0f);

int transformLOC = glGetUniformLocation(Shade.ID,"transform");
//---

while(!glfwWindowShouldClose(window)){

    currtime = findFPS(currtime);//couts fps
    delta += (currtime- prevtime) /fpsLimit;
    prevtime = currtime;
    while(delta >= 1.0){//update the states in here
        processInput(window,wire);
        delta--;
    }


    glClearColor(0.2f, wire.getY(), wire.getX(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Shade2.use();




    //bind texture
//    glBindTexture(GL_TEXTURE_2D, texture);
    Shade.use();//use shader program to render
    glBindVertexArray(VAO);



    trans = glm::rotate(trans, wire.getX(), glm::vec3(0.0, 0.0, 1.0));
    glUniformMatrix4fv(transformLOC, 1, GL_FALSE, glm::value_ptr(trans));

    glDrawElements(GL_TRIANGLES,87,GL_UNSIGNED_INT,0);


    //-----------------------------------------------------------------
        glfwSwapBuffers(window);//renders whatever is put on the window
        glfwPollEvents();//polls output?
}
glDeleteVertexArrays(1, &VAO);
glDeleteBuffers(1, &VBO);
glDeleteBuffers(1, &EBO);
glfwTerminate();
return 0;
}
