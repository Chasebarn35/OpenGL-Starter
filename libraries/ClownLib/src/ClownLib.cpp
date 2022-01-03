#include <ClownLib/ClownLib.h>
void error_callback(int error, const char* description){
    std::cout << "Error " << error << " { " << description << " }" << std::endl;
}


const char * shaderGenerator(std::string fileName,std::string& sourceString){
std::ifstream myFile;
sourceString = "";
try{
myFile.open(fileName);
if(!myFile.good()){
    std::cout << "File " << fileName << " Not Found" << std::endl;

}
    for(std::string sentence;getline(myFile,sentence);){
        sourceString.append(sentence + "\n");//I think this doesnt include the /n??
    }
}
catch(...){
std::cout << "shaderGenerator Failed" << std::endl;
}
if(sourceString == ""){
    std::cout << "File " << fileName << " Not Found" << std::endl;
}
return sourceString.c_str();
}

// std::string vertexShaderStr;
// const char *vertexShaderSource = shaderGenerator("vertexShader.glsl",vertexShaderStr);

//I guess this is my solution for now, where its slightly easier to look at than before. still not great though
const char *vertexShaderSource = R"(
#version 400 compatibility
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 vertexColor;
void main()
{
 gl_Position = vec4(aPos, 1.0);
 vertexColor = aColor;
})";

const char *fragmentShaderSource = R"(
#version 400 compatibility
out vec4 FragColor;
in vec4 vertexColor;
void main()
{
FragColor = vertexColor;
})";


const char *vertexShader2Source = R"(
#version 400 compatibility
layout (location = 0) in vec3 aPos;
void main()
{
 gl_Position = vec4(aPos.x/2 + 0.1f, aPos.y/2 + 0.1f, aPos.z, 1.0);
})";

const char *fragmentShader2Source = R"(
#version 400 compatibility
out vec4 FragColor;
uniform vec4 ourColor;

void main() 
{
FragColor = ourColor;
})";