#include <iostream>
#include "Render/Window.h"

// Window dimensions
const int WIDTH = 1080, HEIGHT = 720;

int main()
{
    Window::initialize(WIDTH, HEIGHT, "Demo");
    Window::colored(0.5f, 0.0f, 1.0f, 1.0f);

    // Game loop
    while (!Window::window_is_closed())
    {
        Window::poll_events();
        Window::clear();
        Window::swap_buffers();
    }

    Window::terminate();
    return 0;
}