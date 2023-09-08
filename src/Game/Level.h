#pragma once
#include "../Render/Graphic/Skybox.h"
#include "Enemy.h"

#include <vector>

class Level
{
	std::vector<Model> static_objects;
	std::vector<Enemy> enemies;
	Skybox* skybox;
	float frame_time; // last delta time
	float delta_time;

	Level(std::string faces, Shader* object_shader, Shader* skybox_shader);
	~Level();
	void draw(Shader* object_shader, Shader* skybox_shader);
};