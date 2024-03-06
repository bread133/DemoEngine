#pragma once
#include "../Render/Graphic/Skybox.h"
#include "Enemy.h"

#include <vector>

/// <summary>
/// �����, ����������� �������� ������� � ����. 
/// ������������ �� ���� ������������ �������, ������ �� ������������ ��������� �������� � ������.
/// ��������� ����� ��������� ������, ������� �������� ������ �������� ����� � main.
/// ����� ����� ��������� � ������ Game.
/// </summary>
class Level
{
	std::string name;
	std::vector<Object*> static_objects;
	std::vector<Enemy*> enemies;
	Skybox* skybox;
	glm::vec3 size;
	bool is_won = false;

	float delta_time = 0.0f;
	float last_frame = 0.0f;
	void add_bullet();
public:
	Level(std::string name, Skybox* skybox);
	~Level();

	void win();
	void draw(Window* window, Camera* camera, Shader* object_shader, Shader* skybox_shader);
	void add_enemy(Enemy* enemy);
	void add_static_object(Object* object);
};