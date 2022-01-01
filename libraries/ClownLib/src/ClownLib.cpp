#include <ClownLib/ClownLib.h>

void error_callback(int error, const char* description){
    std::cout << "Error " << error << " { " << description << " }" << std::endl;
}

const char *vertexShaderSource = "#version 400 compatibility\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *vertexShader2Source = "#version 400 compatibility\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x/2 + 0.1f, aPos.y/2 + 0.1f, aPos.z, 1.0);\n"
"}\0";



const char *fragmentShaderSource = "#version 400 compatibility\n"
"out vec4 FragColor;\n"
"void main()\n" 
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.4f, 1.0f);\n"
"}\0";

const char *fragmentShader2Source = "#version 400 compatibility\n"
"out vec4 FragColor;\n"
"void main()\n" 
"{\n"
"FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\0";