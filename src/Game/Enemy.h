#pragma once
#include <glm/vec3.hpp>
#include "../Render/Graphic/Model.h"

class Enemy
{
	glm::vec3 position;
	Model* model;
	float speed;
	float damage;
	float hp;
	bool alive;
	glm::vec3 get_position();
public:
	Enemy(Model* model, glm::vec3 position, float speed);
	~Enemy();
	void draw();
	bool is_dead();
};