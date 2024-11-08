#include "window.h"

Window::Window(int width, int height, const char* title)
{
    initialize(width, height, title);
}

Window::~Window()
{
    glfwDestroyWindow(window);
}

int Window::initialize(int width, int height, const char* title)
{
    setlocale(LC_ALL, "");
    std::cout << "start GLFW, version OpenGL: 4.6" << std::endl;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// ��� MacOS
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // ��� ��� �������� ����
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "�� ������� ������� GLFW ����" << std::endl;
        glfwTerminate();
        return -1;
    }

    // ������������ ��������� ������ ����� ����
    glfwMakeContextCurrent(window);
    // ������ �� ������� �� ������� ����
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // ������������� glad-���������� (OpenGL � ��� ��������)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "�� ������� ���������������� GLAD-����������" << std::endl;
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);

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

void Window::maximize_window() // TODO
{
    glfwMaximizeWindow(window);
    set_resize();
}

GLFWwindow* Window::get_window()
{
    return this->window;
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

void Window::poll_events_timeout(float timeout)
{
    glfwWaitEventsTimeout(timeout);
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
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}