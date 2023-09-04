#pragma once
#include "../Render/Graphic/Model.h"
#include "../Render/Graphic/Shader.h"
#include "Object.h"
#include "../Render/Window.h"
#include "../Render/Graphic/Camera.h"

#include <glm/vec3.hpp>
#include <vector>

const float			SPEED_ENEMY = 0.5f;
const float			DAMAGE = 5.0f;
const int			HP = 100.0f;

class Enemy : public Object
{
	float speed;
	float damage;
	signed int hp;
	bool alive;
	void get_position(Camera* camera, float delta_time);
public:
	Enemy(Model* model, float pos_x, float pos_y, float pos_z, float speed, float damage, float hp);
	Enemy(Model* model, float pos_x, float pos_y, float pos_z);
	~Enemy();
	void draw(Shader* shader, int WIDTH, int HEIGHT, Camera* camera);
	void is_dead();
};