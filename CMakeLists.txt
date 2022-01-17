cmake_minimum_required(VERSION 3.16.3)

project(OPMain LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

add_executable(${PROJECT_NAME} src/main.cpp src/UserInput.cpp src/Shader.cpp)

add_subdirectory(libraries/glfw)
add_subdirectory(libraries/glad)
add_subdirectory(libraries/glm)

target_include_directories(${PROJECT_NAME} 
    PUBLIC libraries/glfw/include
    PUBLIC libraries/glad/include
    PUBLIC libraries/glm/glm   #Not sure this is right
)

include_directories(${CMAKE_SOURCE_DIR}/libraries/stb_image)

target_link_directories(${PROJECT_NAME}
    PRIVATE libraries/glfw/src
    PRIVATE libraries/glad/src
    )

link_directories(${CMAKE_SOURCE_DIR}/libraries/stb_image)

target_link_libraries(${PROJECT_NAME}
    glfw
    glad
    glm
    -static-libgcc 
    -static-libstdc++
    )

 
