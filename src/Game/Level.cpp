#include "Level.h"

Level::Level(std::string name, Skybox* skybox)
{
	this->name = name;
	this->skybox = skybox;
    size = glm::vec3(0.0f, 0.0f, 0.0f);
}

Level::~Level()
{
    delete skybox;
}

void Level::add_bullet()
{
    
}

void Level::win()
{
	is_won = true;
}

void Level::draw(Window* window, Camera* camera, Shader* object_shader, Shader* skybox_shader)
{
    delta_time = Window::get_delta_time(last_frame);
    camera->input(window, delta_time);

    window->colored(0.5f, 0.5f, 0.5f, 1.0f);
    window->clear();

    object_shader->use();

    for (int i = 0; i < static_objects.size(); i++)
    {
        static_objects[i]->draw(object_shader, window, camera);
    }

    for (int i = 0; i < static_objects.size(); i++)
    {
        enemies[i]->draw(object_shader, window, camera, delta_time);
    }

    skybox->draw(skybox_shader, camera, window, glm::vec3(0.0f), glm::vec3(50.0f));

    window->swap_buffers();
    window->poll_events();
}

void Level::add_enemy(Enemy* enemy)
{
	enemies.push_back(enemy);
}

void Level::add_static_object(Object* object)
{
	static_objects.push_back(object);
}