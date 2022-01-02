#include <ClownLib/ClownLib.h>
void error_callback(int error, const char* description){
    std::cout << "Error " << error << " { " << description << " }" << std::endl;
}


const char * shaderGenerator(std::string fileName,std::string& sourceString){
std::ifstream myFile;
sourceString = "";
try{
myFile.open(fileName);
for(std::string sentence;getline(myFile,sentence);){
sourceString.append(sentence + "\n");//I think this doesnt include the /n??
}
}
catch(...){
throw "shaderGenerator Failed";
}
return sourceString.c_str();
}

std::string vertexShaderStr;
const char *vertexShaderSource = shaderGenerator("vertexShader.glsl",vertexShaderStr);

// const char *vertexShaderSource = "#version 400 compatibility\n"
// "layout (location = 0) in vec3 aPos;\n"
// "void main()\n"
// "{\n"
// " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
// "}\0";

const char *fragmentShaderSource = 
"#version 400 compatibility\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;"
"void main()\n" 
"{\n"
"FragColor = vertexColor;\n"
"}\0";


const char *vertexShader2Source = "#version 400 compatibility\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x/2 + 0.1f, aPos.y/2 + 0.1f, aPos.z, 1.0);\n"
"}\0";

const char *fragmentShader2Source = "#version 400 compatibility\n"
"out vec4 FragColor;\n"
"void main()\n" 
"{\n"
"FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\0";