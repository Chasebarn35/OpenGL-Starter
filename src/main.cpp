#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"
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

Shader Shade("resources/Shaders/vertexShader.glsl","resources/Shaders/FragmentShader.glsl");//probably the wrong directories lol
Shader Shade2("resources/Shaders/vertexShader2.glsl","resources/Shaders/fragmentShader2.glsl");

Shade.use();



//-----------------------------------------------------------------------

float vertices[] = {
        //positions           //colors            //textures
         0.5f,  0.6f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.75f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, .75f, // top left 
         0.0f,  1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   0.5f, 1.0f  //top middle
};
unsigned int indices[]{
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle
        0, 3, 4  // third triangle
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
stbi_set_flip_vertically_on_load(true);
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



//---
int vertexTriangleColor = glGetUniformLocation(Shade2.ID, "ourColor");
int vertexTriangleRotation = glGetUniformLocation(Shade.ID, "rotation");


//---

StateMachine wire;
double currtime = glfwGetTime();
double prevtime = currtime;
double delta = 0;
double fpsLimit = 1.0/60.0;
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
    glBindTexture(GL_TEXTURE_2D, texture);
    Shade.use();//use shader program to render
    glBindVertexArray(VAO);


    glUniform1f(vertexTriangleRotation,wire.getX());
    glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);


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
