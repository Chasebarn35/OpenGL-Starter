#include <iostream>
#include <exception>
#include <fstream>
#include <string>

void error_callback(int error, const char* description);
const char * shaderGenerator(std::string fileName);
extern std::string vertexShaderStr;
extern const char *vertexShaderSource;
extern const char *vertexShader2Source;
extern const char *fragmentShaderSource;
extern const char *fragmentShader2Source;