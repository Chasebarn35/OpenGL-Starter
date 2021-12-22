cmake_minimum_required(VERSION 3.16.3)
project(OPMain)
add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(libraries/glfw)
add_subdirectory(libraries/glad)

target_include_directories(${PROJECT_NAME} 
    PUBLIC libraries/glfw/include
    PUBLIC libraries/glad/include
)

target_link_directories(${PROJECT_NAME} 
    PRIVATE libraries/glfw/src
    PRIVATE libraries/glad/src
    )

target_link_libraries(${PROJECT_NAME}
    glfw
    glad
    )   