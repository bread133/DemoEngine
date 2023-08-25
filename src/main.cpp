#include "Render/Window.h"
#include "Render/Graphic/Shader.h"
#include "Render/Graphic/Mesh.h"
#include "Render/Graphic/Camera.h"
#include "Render/Graphic/Texture.h"

// Window dimensions
const int WIDTH = 1080, HEIGHT = 720;

int main()
{
    Window* window = new Window();
    window->initialize(WIDTH, HEIGHT, "Demo");
    window->colored(0.3f, 0.3f, 0.3f, 0.7f);

    Mesh* mesh = new Mesh();
    mesh->load_buffer(0, 3,
        {
            -1.0f,   -1.0f, -1.0f,  // Треугольник 1 : начало
            -1.0f,   -1.0f, 1.0f,
            -1.0f,  1.0f,   1.0f
        });

    Texture* texture = new Texture();
    texture->create_texture("D://Download/PXaFcQ10a9k.png");

    /*mesh->load_buffer(1, 3,
        {
            0.583f,  0.771f,  0.014f,
            0.609f,  0.115f,  0.436f,
            0.327f,  0.483f,  0.844f
        });*/

    texture->load(2, {
        0.0f, 0.0f,  // lower-left corner  
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f   // top-center corner
        });
    
    Shader* shader = load("C://Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Shaders/figure_texture.glslv", 
        "C://Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Shaders/figure_texture.glslf");

    Camera* camera = new Camera();
    GLuint matrix_id = shader->get_uniform_location(camera->get_MVP());
    Mesh::depth_mode();

    // Игровой цикл
    float last_delta_time = 0;
    while (!window->window_is_closed())
    {
        window->clear();

        shader->get_uniform_matrix(matrix_id, camera->get_MVP());
        shader->use();

        mesh->bind();
        mesh->draw(12 * 3);

        texture->bind();

        window->swap_buffers();
        window->poll_events();

        float delta_time = Window::get_delta_time(last_delta_time);
        camera->input(window, delta_time);

        if (window->is_exit()) {
            break;
        }
    }

    delete camera;
    delete mesh;
    delete shader;
    window->terminate();
    delete window;

    return 0;
}