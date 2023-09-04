#include "Render/Graphic/Shader.h"
#include "Render/Graphic/Model.h"
#include "Render/Graphic/Camera.h"
#include "Render/Window.h"

#include "Game/Enemy.h"
#include "Render/Graphic/Skybox.h"

// settings
const unsigned int WIDTH = 1024;
const unsigned int HEIGHT = 720;

int main()
{
    // window initialize
    Window* window = new Window(WIDTH, HEIGHT, "Demo");
    //window->set_resize();
    Window::depth_test();
    // Enables Cull Facing
    glEnable(GL_CULL_FACE);
    // Keeps front faces
    //glCullFace(GL_FRONT);
    // Uses counter clock-wise standard
    //glFrontFace(GL_CCW);
    /*-------------------------------------------------------------*/

    Shader* object_shader = new Shader("C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Shaders/figure_texture.glslv", 
        "C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Shaders/figure_texture.glslf");
   Shader* skybox_shader = new Shader("C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Shaders/skybox_shader.glslv",
        "C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Shaders/skybox_shader.glslf");

    // skybox texture loading
    std::vector<std::string> faces
    {
        "C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Skyboxes/Space/right.jpg",
        "C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Skyboxes/Space/left.jpg",
        "C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Skyboxes/Space/top.jpg",
        "C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Skyboxes/Space/bottom.jpg",
        "C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Skyboxes/Space/front.jpg",
        "C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Skyboxes/Space/back.jpg"
    };
    Skybox* skybox_cube = new Skybox(faces, skybox_shader);
    /*------------------------------------------------------------*/

    Object* cube = new Object(new Model("C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Models/test_cube/test_cube.obj",
        false), 0.0f, 0.0f, 0.0f);
    object_shader->use();
    object_shader->set_int("skybox", 0);

    skybox_shader->use();
    skybox_shader->set_int("skybox", 0);

    /*Enemy* enemy = new Enemy(new Model(
        "C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Models/test_cube/test_cube.obj",
        false), 0.0f, 20.0f, 0.0f);*/

    //Window::polygon_mode();

    float delta_time = 0.0f;
    float last_frame = 0.0f;
    Camera* camera = new Camera(glm::vec3(0.0f, 5.0f, 5.0f), true);

    while (!(window->window_is_closed()))
    {
        delta_time = Window::get_delta_time(last_frame);
        camera->input(window, delta_time);
        if (window->is_exit())
            break;

        window->colored(0.5f, 0.5f, 0.5f, 1.0f);
        window->clear();

        object_shader->use();
        camera->mvp_transformation(WIDTH, HEIGHT, object_shader, glm::vec3(0.0f));
        cube->draw(object_shader);
        //enemy->draw(shader, WIDTH, HEIGHT, camera);
        skybox_cube->draw(skybox_shader, camera, WIDTH, HEIGHT, glm::vec3(0.0f), glm::vec3(10.0f, 10.0f, 10.0f));

        window->swap_buffers();
        window->poll_events();
    }

    window->terminate();

    std::cin.get();
    //delete enemy;
    delete skybox_cube;
    delete skybox_shader;
    delete camera;
    delete cube;
    delete object_shader;
    delete window;
    return 0;
}
