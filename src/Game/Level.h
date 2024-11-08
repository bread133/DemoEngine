#pragma once
#include "../Render/Graphic/Skybox.h"
#include "Enemy.h"
#include "Bullet.h"

#include <vector>
#include <thread>
#include <src/Physic/Map.h>

/// <summary>
/// �����, ����������� �������� ������� � ����. 
/// ������������ �� ���� ������������ �������, ������ �� ������������ ��������� �������� � ������.
/// ��������� ����� ��������� ������, ������� �������� ������ �������� ����� � main.
/// ����� ����� ��������� � ������ Game.
/// </summary>
class Level
{
	Camera* camera;
	std::string name;
	std::vector<Object*> static_objects;
	std::vector<Object*> enemies;
	Map* map;
	Bullet* bullet;
	std::vector<Object*> bullets;
	Skybox* skybox;
	glm::vec3 size;
	bool is_win = false;

	float delta_time = 0.0f;
	float last_frame = 0.0f;
	void add_bullet(Window* window);
	void load_vector(std::vector<Object*> objects);
	void draw_vector(std::vector<Object*> objects, Window* window, Shader* object_shader, Shader* skybox_shader);
	void set_status(Window* window);
public:
	Level(std::string name, Skybox* skybox, glm::vec3 position, bool is_fly);
	Level(std::string name, Skybox* skybox, Camera* camera);
	~Level();

	void win();
	void load();
	void load_bullet();
	void draw(Window* window, Shader* object_shader, Shader* skybox_shader);
	void add_enemy(Enemy* enemy);
	void add_static_object(Object* object);

	bool get_status();
};