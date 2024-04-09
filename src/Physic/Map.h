#pragma once
#include "src/Game/Object.h"
#include "src/Game/Enemy.h"
#include "src/Game/Bullet.h"
#include "src/Physic/Collision.h"
#include "src/Debug/FileHandler.h"

class Map
{
	std::vector<Object*> objects;
	void collision_detector(Object* first);
public:
	glm::vec3 gravity = glm::vec3(0.0f, -0.1f, 0.0f); // ускорение свободного падения

	Map();
	~Map();
	void add_object(Object* object);
	void remove_object(Object* object);
	void gravity_step(Object* object, float delta_time);
	void load();
	Object* back_object();
	void draw(Shader* object_shader, Window* window, Camera* camera, float delta_time); 
};