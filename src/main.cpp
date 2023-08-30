#include "Render/Graphic/Shader.h"
#include "Render/Graphic/Model.h"
#include "Render/Graphic/Camera.h"
#include "Render/Window.h"

#include "Game/Enemy.h"

// settings
const unsigned int WIDTH = 1024;
const unsigned int HEIGHT = 720;

int main()
{
    Window* window = new Window();
    window->initialize(WIDTH, HEIGHT, "Demo");
    window->set_resize();

    Window::depth_test();

    // build and compile shaders
    // -------------------------
    Shader* shader = new Shader("C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Shaders/figure_texture.glslv", 
        "C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Shaders/figure_texture.glslf");

    // load models
    // -----------
    Model* test_model = new Model("C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Models/test_cube/test_cube.obj",
        false);
   Model* test_model_enemy = new Model("C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Models/test_enemy/test_enemy.obj", 
        false);
   Enemy* enemy = new Enemy(test_model_enemy, 0.0f, 5.0f, 0.0f);

    // Window::polygon_mode();
    
    // timing
    float delta_time = 0.0f;
    float last_frame = 0.0f;

    // camera
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f));

    // render loop
    while (!(window->window_is_closed()))
    {
        delta_time = Window::get_delta_time(last_frame);
        camera->input(window, delta_time);
        if (window->is_exit())
            break;
        // render
        // ------
        window->colored(0.5f, 0.5f, 0.5f, 1.0f);
        window->clear();

        // don't forget to enable shader before setting uniforms
        shader->use();

        camera->mvp_transformation(WIDTH, HEIGHT, shader);

        test_model->draw(shader);
        enemy->draw(shader);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        window->swap_buffers();
        window->poll_events();
    }

    window->terminate();

    delete enemy;
    delete camera;
    delete test_model;
    delete shader;
    delete window;

    return 0;
}
