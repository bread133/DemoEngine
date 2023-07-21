cmake_minimum_required(VERSION 3.26 FATAL_ERROR)
set(PROJECT_NAME DemoEngine)
set(CMAKE_CXX_STANDART 20)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
src/main.cpp
src/Render/Window.cpp
src/Render/Window.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)
