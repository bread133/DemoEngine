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

void Level::add_bullet(Camera* camera, Window* window)
{
    if (glfwGetMouseButton(window->get_window(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        Bullet* bullet = new Bullet(new Model(
            "C://Users/bread/source/repos/DemoEngineWithCMake/src/Render/Resources/Models/golf_ball/model.obj",
            false), glm::vec3(camera->get_position().x, camera->get_position().y - 0.5f, camera->get_position().z),
            glm::vec3(1.0f), 5.0f, 10.0f);
        bullets.push_back(bullet);
    }
}

void Level::win()
{
	is_won = true;
}

void Level::draw_vector(std::vector<Object*> objects, Window* window, Camera* camera, Shader* object_shader, Shader* skybox_shader)
{
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->draw(object_shader, window, camera, delta_time);
    }
}

void Level::draw(Window* window, Camera* camera, Shader* object_shader, Shader* skybox_shader)
{
    // �����
    delta_time = Window::get_delta_time(last_frame);
    camera->input(window, delta_time);

    // ������� ����
    // window->colored(0.5f, 0.5f, 0.5f, 1.0f);
    window->clear();

    // ������
    object_shader->use();

    // ����������� �������
    draw_vector(static_objects, window, camera, object_shader, skybox_shader);

    // �����
    draw_vector(enemies, window, camera, object_shader, skybox_shader);

    // ��������
    /*std::thread th([&]() 
    { 
        add_bullet(camera, window); 
        draw_vector(bullets, window, camera, object_shader, skybox_shader); 
    });*/

    add_bullet(camera, window);
    draw_vector(bullets, window, camera, object_shader, skybox_shader);

    // ��������
    skybox->draw(skybox_shader, camera, window, glm::vec3(0.0f), glm::vec3(50.0f));

    // th.join(); - ���� ������, ��� ������� �������
    // ����� � ����� ������
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