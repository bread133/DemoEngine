cmake_minimum_required(VERSION 3.26 FATAL_ERROR)
set(PROJECT_NAME DemoEngine)

set(CMAKE_CXX_STANDARD 20)

project(${PROJECT_NAME})

include_directories(.)

add_library(DemoEngineLibrary
src/Render/Window.cpp
src/Render/Graphic/Shader.cpp
src/Render/Graphic/Mesh.cpp
src/Render/Graphic/Camera.cpp
src/Render/Graphic/Model.cpp
src/Render/Graphic/Skybox.cpp
src/Render/Graphic/Sprite.cpp

src/Game/Object.cpp
src/Game/Enemy.cpp
src/Game/Level.cpp)

add_executable(${PROJECT_NAME}
src/main.cpp
src/Render/Window.cpp
src/Render/Window.h
src/Render/Graphic/Shader.cpp
src/Render/Graphic/Shader.h
src/Render/Graphic/Mesh.cpp
src/Render/Graphic/Mesh.h
src/Render/Graphic/Camera.cpp
src/Render/Graphic/Camera.h
src/Render/Graphic/Model.cpp
src/Render/Graphic/Model.h
src/Render/Graphic/Skybox.cpp
src/Render/Graphic/Skybox.h
src/Render/Graphic/Sprite.cpp
src/Render/Graphic/Sprite.h
src/Render/Graphic/Vertex.h
src/Render/Graphic/Texture.h
external/stb/stb_image.h

src/Game/Object.cpp
src/Game/Object.h
src/Game/Enemy.cpp
src/Game/Enemy.h
src/Game/Level.cpp
src/Game/Level.h
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(DemoEngineLibrary PUBLIC glfw)


add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)
target_link_libraries(DemoEngineLibrary PUBLIC glad)

add_subdirectory(external/assimp)
target_link_libraries(${PROJECT_NAME} PUBLIC assimp)
target_link_libraries(DemoEngineLibrary PUBLIC assimp)

include_directories(external/glm)
include_directories(external/stb)

include_directories(src/Render/Resources)