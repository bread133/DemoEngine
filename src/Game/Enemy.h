#pragma once
#include "../Render/Graphic/Model.h"
#include "../Render/Graphic/Shader.h"

#include <glm/vec3.hpp>
#include <vector>

const float SPEED_ENEMY = 2.5f;
const float DAMAGE = 5.0f;
const float HP = 100.0f;

class Enemy
{
	glm::vec3 position;
	Model* model;
	float speed;
	float damage;
	float hp;
	bool alive;
	void move();
public:
	Enemy(Model* model, float pos_x, float pos_y, float pos_z, float speed, float damage, float hp);
	Enemy(Model* model, float pos_x, float pos_y, float pos_z);
	~Enemy();
	void draw(Shader *shader);
	bool is_dead();
};