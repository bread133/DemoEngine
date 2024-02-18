#include "Render/Graphic/Shader.h"
#include "Render/Graphic/Model.h"
#include "Render/Graphic/Camera.h"
#include "Render/Window.h"

#include "Game/Enemy.h"
#include "Render/Graphic/Skybox.h"

#include <filesystem>
#include <iostream>
#include <string>

// settings
unsigned int WIDTH;
unsigned int HEIGHT;

const char* get_path_of_project(std::string file)
{
    std::string path_string =
        std::filesystem::current_path().string(); // текущая папка это билд

    char* cstr = new char[path_string.length() + file.length() + 5];
    path_string.append("\\..\\");
    path_string.append(file);
    strcpy(cstr, path_string.c_str());

    return cstr;
}

int main()
{
    std::cout << "Enter a width: ";
    std::cin >> WIDTH;

    std::cout << "Enter a height: ";
    std::cin >> HEIGHT;

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
    //Window::polygon_mode();
    /*-------------------------------------------------------------*/

    Shader* object_shader = new Shader(get_path_of_project("src\\Render\\Resources\\Shaders\\figure_texture.glslv"),
        get_path_of_project("src\\Render\\Resources\\Shaders\\figure_texture.glslf"));
   Shader* skybox_shader = new Shader(get_path_of_project("src\\Render\\Resources\\Shaders\\skybox_shader.glslv"),
       get_path_of_project("src\\Render\\Resources\\Shaders\\skybox_shader.glslf"));

    // skybox texture loading
    std::vector<std::string> faces
    {
        get_path_of_project("src\\Render\\Resources\\Skyboxes\\Space\\right.jpg"),
        get_path_of_project("src\\Render\\Resources\\Skyboxes\\Space\\left.jpg"),
        get_path_of_project("src\\Render\\Resources\\Skyboxes\\Space\\top.jpg"),
        get_path_of_project("src\\Render\\Resources\\Skyboxes\\Space\\bottom.jpg"),
        get_path_of_project("src\\Render\\Resources\\Skyboxes\\Space\\front.jpg"),
        get_path_of_project("src\\Render\\Resources\\Skyboxes\\Space\\back.jpg")
    };
    Skybox* skybox_cube = new Skybox(faces, skybox_shader);
    /*------------------------------------------------------------*/

    Object* static_object = new Object(new Model(get_path_of_project("src\\Render\\Resources\\Models\\saul_goodman/model.obj"),
        false), glm::vec3(0.0f), glm::vec3(2.0));
    object_shader->use();

    skybox_shader->use();
    skybox_shader->set_int("skybox", 0);

    /*Enemy* enemy = new Enemy(new Model(
        "C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Models/spaceship_0/spaceship.obj",
        false), glm::vec3(5.0f), glm::vec3(0.01f), 0.2f, 10.0f, 100.0f);*/

    Enemy* enemy = new Enemy(new Model(get_path_of_project("src\\Render\\Resources\\Models\\Spaceship/spaceship.obj"),
        false), glm::vec3(5.0f));

    float delta_time = 0.0f;
    float last_frame = 0.0f;
    Camera* camera = new Camera(glm::vec3(0.0f, 5.0f, 5.0f), true);

    /*-------------------------------------------------------------*/
    while (!(window->window_is_closed()))
    {
        delta_time = Window::get_delta_time(last_frame);
        camera->input(window, delta_time);
        if (window->is_exit())
            break;

        window->colored(0.5f, 0.5f, 0.5f, 1.0f);
        window->clear();

        object_shader->use();

        static_object->draw(object_shader, window, camera);
        enemy->draw(object_shader, window, camera, delta_time);
        skybox_cube->draw(skybox_shader, camera, window, glm::vec3(0.0f), glm::vec3(50.0f));

        window->swap_buffers();
        window->poll_events();
    }

    /*-------------------------------------------------------------*/
    window->terminate();
    // std::cin.get();

    delete enemy;
    delete skybox_cube;
    delete skybox_shader;
    delete camera;
    delete static_object;
    delete object_shader;
    delete window;

    return 0;
}
