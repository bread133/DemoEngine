#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Render/Window.h"

// Window dimensions
const GLuint WIDTH = 1080, HEIGHT = 720;

int main()
{
    Window::initialize(WIDTH, HEIGHT, "Demo");
    Window::colored(1.0f, 1.0f, 1.0f, 0.0f);
    // Game loop
    while (true)
    {
        
        Window::swap_buffers();
    }

    Window::terminate();
    return 0;
}