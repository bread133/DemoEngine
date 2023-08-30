#include "window.h"

int Window::initialize(int width, int height, const char* title)
{
    setlocale(LC_ALL, "");
    std::cout << "Запуск GLFW, версия OpenGL: 3.3" << std::endl;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Не удалось создать GLFW окно" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Не удалось инициализировать GLAD-библиотеку" << std::endl;
        return -1;
    }

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

float Window::get_delta_time(float &last)
{
    float current_frame = static_cast<float>(glfwGetTime());
    float delta_time = current_frame - last;
    last = current_frame;
    return delta_time;
}

bool Window::is_exit()
{
    return glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

void Window::set_resize()
{
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void Window::depth_test()
{
    glEnable(GL_DEPTH_TEST);
}

void Window::polygon_mode()
{
    // draw in wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

// подгон изображения при изменении размера окна
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}