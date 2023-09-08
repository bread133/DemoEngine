#pragma once
#include "../Render/Graphic/Model.h"
#include "../Render/Graphic/Shader.h"
#include "Object.h"
#include "../Render/Window.h"
#include "../Render/Graphic/Camera.h"

#include <glm/vec3.hpp>
#include <vector>

const float			SPEED_ENEMY = 1.5f;
const float			DAMAGE = 5.0f;
const int			HP = 100.0f;
const float			DISTANCE = 3.0f;

class Enemy : public Object
{
	float speed;
	float damage;
	signed int hp;
	bool alive;
	float distance;
	void get_position(Camera* camera, float delta_time);
public:
	Enemy(Model* model, glm::vec3 position, glm::vec3 scale, float speed, float damage, float hp, float distance);
	Enemy(Model* model, glm::vec3 position);
	~Enemy();
	void draw(Shader* shader, Window* window, Camera* camera, float delta_time);
	void is_dead();
};