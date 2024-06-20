#include "Level.h"

Level::Level(std::string name, Skybox* skybox, glm::vec3 position, bool is_fly, Player* player) :
    name(name),
    skybox(skybox),
    player(player)
{
    camera = new Camera(position, is_fly);
    map = new Map(player);
}

Level::Level(std::string name, Skybox* skybox, Camera* camera, Player* player) :
    name(name),
    skybox(skybox),
    camera(camera),
    player(player)
{
    map = new Map(player);
}

bool Level::get_status()
{
    return is_win;
}

void Level::load_bullet(bool has_impulse)
{
    map->load_bullet(has_impulse);
}

Level::~Level()
{
    delete skybox;
    delete camera;
}

void Level::win()
{
	is_win = true;
}

void Level::load()
{
    map->load();
}

// тут пока затычка, пока не реализована коллизия
void Level::set_status(Window* window)
{
    if (glfwGetKey(window->get_window(), GLFW_KEY_0) == GLFW_PRESS) 
    {
        window->poll_events_timeout(1.0f);
        is_win = true;
    }}

void Level::draw(Window* window, Shader* object_shader, Shader* skybox_shader)
{
    //std::cout << camera->get_direction().x << ' ' << camera->get_direction().y
    //    << ' ' << camera->get_direction().z << std::endl;

    // время
    delta_time = Window::get_delta_time(last_frame);
    camera->input(window, delta_time);

    // очистка окна
    window->clear();

    // шейдер
    object_shader->use();

    if (glfwGetMouseButton(window->get_window(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        map->add_bullet(window, camera);
    // отрисовка всех объектов на карте
    map->draw(object_shader, window, camera, delta_time);
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
	map->add_object(enemy);
}

void Level::add_static_object(Object* object)
{
	map->add_object(object);
}

void Level::add_light(LightPoint* light)
{
    if (!map)
        throw("Неинициализирована переменная map");
    map->add_light(light);
}

void Level::remove_light(LightPoint* light)
{
    if (!map)
        throw("Неинициализирована переменная map");
    map->remove_light(light);
}

