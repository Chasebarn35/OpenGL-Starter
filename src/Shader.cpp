#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath){
using std::string;
using std::ifstream;
ifstream vertFile(vertexPath);

if(!vertFile.good() || !vertFile.is_open()){
    std::cout <<"VERTICAL SHADER file not at directory" << std::endl;
}

ifstream fragFile(fragmentPath);

if(!fragFile.good() || !fragFile.is_open()){
    std::cout <<"FRAGMENT SHADER file not at directory" << std::endl;
}

string vertString((std::istreambuf_iterator<char>(vertFile)),(std::istreambuf_iterator<char>()));
string fragString((std::istreambuf_iterator<char>(fragFile)),(std::istreambuf_iterator<char>()));

const char * vertData = vertString.c_str();
const char * fragData = fragString.c_str();

GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertShader, 1, &vertData,NULL);
glCompileShader(vertShader);
ShaderSuccess(vertShader,"VERTEX");

GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragShader, 1, &fragData,NULL);
glCompileShader(fragShader);
ShaderSuccess(fragShader,"FRAGMENT");

ID = glCreateProgram();
glAttachShader(ID,vertShader);
glAttachShader(ID,fragShader);
glLinkProgram(ID);
LinkSuccess(ID,"PROGRAM");

}

void Shader::use()
{
    glUseProgram(ID);
}
