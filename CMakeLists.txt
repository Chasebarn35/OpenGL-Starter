cmake_minimum_required(VERSION 3.16.3)

project(OPMain LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

add_executable(${PROJECT_NAME} src/main.cpp src/UserInput.cpp)

add_subdirectory(libraries/glfw)
add_subdirectory(libraries/glad)
add_subdirectory(libraries/ClownLib)

target_include_directories(${PROJECT_NAME} 
    PUBLIC libraries/glfw/include
    PUBLIC libraries/glad/include
    PUBLIC libraries/ClownLib/include
)

target_link_directories(${PROJECT_NAME}
    PRIVATE libraries/glfw/src
    PRIVATE libraries/glad/src
    PRIVATE libraries/ClownLib/src
    )

target_link_libraries(${PROJECT_NAME}
    glfw
    glad
    ClownLib
    -static-libgcc 
    -static-libstdc++
    )   