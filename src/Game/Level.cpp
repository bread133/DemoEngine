#include "Level.h"

Level::Level(std::string name, Skybox* skybox, glm::vec3 position, bool is_fly) :
    name(name),
    skybox(skybox)
{
    camera = new Camera(position, is_fly);
}

bool Level::get_status()
{
    return is_win;
}

void Level::load_bullet()
{
    bullet = new Bullet(new Model(
        "C://Users/bread/source/repos/DemoEngineWithCMake/src/Render/Resources/Models/golf_ball/model.obj",
        false), glm::vec3(0.0f),
        glm::vec3(1.0f), 5.0f, 10.0f);
}

Level::Level(std::string name, Skybox* skybox, Camera* camera) :
    name(name),
    skybox(skybox),
    camera(camera)
{
}

Level::~Level()
{
    delete skybox;
    delete camera;
}

void Level::add_bullet(Window* window)
{
    if (glfwGetMouseButton(window->get_window(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        bullet->set_start_position(camera);
        bullets.push_back(new Bullet(bullet));
        bullets.back()->load();
    }
}

void Level::win()
{
	is_win = true;
}

void Level::load()
{
    load_vector(static_objects);
    load_vector(enemies);
}

void Level::draw_vector(std::vector<Object*> objects, Window* window, Shader* object_shader, Shader* skybox_shader)
{
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->draw(object_shader, window, camera, delta_time);
    }
}

void Level::load_vector(std::vector<Object*> objects)
{
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->load();
    }
}

// тут пока затычка, пока не реализована коллизия
void Level::set_status(Window* window)
{
    if (glfwGetKey(window->get_window(), GLFW_KEY_0) == GLFW_PRESS) 
    {
        window->poll_events_timeout(1.0f);
        is_win = true;
    }
}

void Level::draw(Window* window, Shader* object_shader, Shader* skybox_shader)
{
    // время
    delta_time = Window::get_delta_time(last_frame);
    camera->input(window, delta_time);

    // очистка окна
    window->clear();

    // шейдер
    object_shader->use();

    // статические объекты
    draw_vector(static_objects, window, object_shader, skybox_shader);

    // враги
    draw_vector(enemies, window, object_shader, skybox_shader); // error

    // выстрелы 
    // TODO: многопоточность

    /*std::thread th([&]() 
    { 
        add_bullet(camera, window); 
        draw_vector(bullets, window, camera, object_shader, skybox_shader); 
    });*/

    add_bullet(window);
    draw_vector(bullets, window, object_shader, skybox_shader); // тут вылетает ошибка
    /*---------------------------------------------------------------------------*/
    // скайбокс
    skybox->draw(skybox_shader, camera, window, glm::vec3(0.0f), glm::vec3(50.0f));
    /*---------------------------------------------------------------------------*/

    // th.join(); - пока неясно, как сделать красиво
    /*---------------------------------------------------------------------------*/
    // условие выигрыша
    set_status(window);
    // инпут и смена кадров
    window->swap_buffers();
    window->poll_events();
    // window->poll_events_timeout(0.1f); - нужно нормально имплементировать
}

void Level::add_enemy(Enemy* enemy)
{
	enemies.push_back(enemy);
}

void Level::add_static_object(Object* object)
{
	static_objects.push_back(object);
}