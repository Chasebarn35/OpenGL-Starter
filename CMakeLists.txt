cmake_minimum_required(VERSION 3.16.3)
project(OPMain)
add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(libraries/glfw)
add_subdirectory(libraries/glad)#doesnt do anything

target_include_directories(${PROJECT_NAME} 
    PUBLIC libraries/glfw/include
)

target_link_directories(${PROJECT_NAME} 
    PRIVATE libraries/glfw/src
)

target_link_libraries(${PROJECT_NAME}
    glfw
    )   