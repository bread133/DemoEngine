#include "window.h"

GLFWwindow* Window::window;

int Window::initialize(int width, int height, const char* title)
{
    setlocale(LC_ALL, "");
    std::cout << "Запуск GLFW, версия OpenGL: 3.3" << std::endl;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(window);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    // Define the viewport dimensions
    glViewport(0, 0, width, height);
    return 0;
}

void Window::terminate()
{
    glfwTerminate();
}

void Window::colored(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);
}

void Window::swap_buffers()
{
    glfwSwapBuffers(window);
}

void Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::window_is_closed()
{
    return glfwWindowShouldClose(window);
}

void Window::poll_events()
{
    glfwPollEvents();
}
