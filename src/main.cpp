#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Render/Window.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 1080, HEIGHT = 720;

// The MAIN function, from here we start the application and run the game loop
int main()
{
    Window::initialize(WIDTH, HEIGHT, "Demo");
    // Game loop
    while (true)
    {
        glfwPollEvents();

        Window::colored(1.0f, 0.0f, 1.0f, 0.5f);
        Window::swap_buffers();
    }

    Window::terminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}