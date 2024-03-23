#include "src/Game/Game.h"
#include <filesystem>
#include <iostream>

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
    std::cout << get_path_of_project("src\\Render\\Resources\\Shaders\\figure_texture.glslv") << std::endl;

    std::cout << "Enter a width: ";
    std::cin >> WIDTH;

    std::cout << "Enter a height: ";
    std::cin >> HEIGHT;

    // window initialize
    Window* window = new Window(WIDTH, HEIGHT, "Demo");
    // window->maximize_window();
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

    std::vector<std::string> faces_2
    {
        get_path_of_project("src\\Render\\Resources\\Skyboxes\\Sky\\right.jpg"),
        get_path_of_project("src\\Render\\Resources\\Skyboxes\\Sky\\left.jpg"),
        get_path_of_project("src\\Render\\Resources\\Skyboxes\\Sky\\top.jpg"),
        get_path_of_project("src\\Render\\Resources\\Skyboxes\\Sky\\bottom.jpg"),
        get_path_of_project("src\\Render\\Resources\\Skyboxes\\Sky\\front.jpg"),
        get_path_of_project("src\\Render\\Resources\\Skyboxes\\Sky\\back.jpg")
    };
    // Skybox* skybox_cube = new Skybox(faces, skybox_shader);

    // float delta_time = 0.0f;
    // float last_frame = 0.0f;
    Camera* camera = new Camera(glm::vec3(0.0f), true);
    /*------------------------------------------------------------*/
    Game* game = new Game(window, object_shader, skybox_shader);
    /*------------------------------------------------------------*/
    Level* test_level_1 = new Level("default_1", new Skybox(faces, 
        skybox_shader), camera);

    Level* test_level_2 = new Level("default_2", new Skybox(faces_2,
        skybox_shader), camera);
    
    // Object* static_object = new Object(new Model(get_path_of_project("src/Render/Resources/Models/saul_goodman/model.obj"),
    //     false), glm::vec3(0.0f), glm::vec3(2.0));
    // test_level_1->add_static_object(new Object(new Model(get_path_of_project(
    //     "src\\Render\\Resources\\Models\\saul_goodman/model.obj"),
    //     false), glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(2.0)));

    // test_level_2->add_static_object(new Object(new Model(get_path_of_project(
    //     "src\\Render\\Resources\\Models\\saul_goodman/model.obj"),
    //     false), glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(2.0)));

    // Enemy* enemy = new Enemy(new Model(get_path_of_project("src\\Render\\Resources\\Models\\Spaceship/spaceship.obj"),
    //     false), glm::vec3(5.0f));
    test_level_1->add_enemy(new Enemy(new Model(
        "C://Users/bread/source/repos/DemoEngineWithCMake/src/Render/Resources/Models/test_enemy/test_enemy.obj",
        false), glm::vec3(5.0f)));

    // test_level_2->add_enemy(new Enemy(new Model(
    //     "C://Users/bread/source/repos/DemoEngineWithCMake/src/Render/Resources/Models/test_enemy/test_enemy.obj",
    //     false), glm::vec3(5.0f)));

    /*object_shader->use();

    skybox_shader->use();
    skybox_shader->set_int("skybox", 0);*/

    /*------------------------------------------------------------*/
    game->add_level(test_level_1);
    game->add_level(test_level_2);
    /*Enemy* enemy = new Enemy(new Model(
        "C:/Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Resources/Models/spaceship_0/spaceship.obj",
        false), glm::vec3(5.0f), glm::vec3(0.01f), 0.2f, 10.0f, 100.0f);*/

    /*-------------------------------------------------------------*/

    //while (!(window->window_is_closed()))
    //{
    //    // delta_time = Window::get_delta_time(last_frame);
    //    // camera->input(window, delta_time);
    //    test_level_1->draw(window, object_shader, skybox_shader);
    //    if (window->is_exit())
    //        break;

    //    // window->colored(0.5f, 0.5f, 0.5f, 1.0f);
    //    // window->clear();

    //    // object_shader->use();

    //    // static_object->draw(object_shader, window, camera);
    //    // enemy->draw(object_shader, window, camera, delta_time);
    //    // skybox_cube->draw(skybox_shader, camera, window, glm::vec3(0.0f), glm::vec3(50.0f));

    //    // window->swap_buffers();
    //    // window->poll_events();
    //}
    game->start();
    /*-------------------------------------------------------------*/

    // window->terminate();

    // delete enemy;
    // delete skybox_cube;
    // delete skybox_shader;
    // delete camera;
    // delete static_object;
    // delete object_shader;
    // delete window;
    std::cin.get();
    delete game;
    return 0;
}
