#include <ClownLib.h>


void error_callback(int error, const char* description){
    std::cout << "Error " << error << " { " << description << " }" << std::endl;
}

