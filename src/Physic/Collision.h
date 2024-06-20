#pragma once

#include <src/Physic/Collider.h>
#include <src/Game/Object.h>

#include <utility>
#include <glm/vec3.hpp>
#include <string>
#include <typeinfo>

const float MARGIN = 0.5f;

class Collision
{
	Collider* first;
	glm::vec3 position_first;
	Object* object_first;

	Collider* second;
	glm::vec3 position_second;
	Object* object_second;

	bool parallelepiped_parallelepiped();
	bool sphere_sphere();
	bool parallelepiped_sphere();

	// const int* table_of_collide = new int[]{
					// sphere	paral-ed			none
	// sphere			1,			1,				0,
	//paral-ed		1,			1,				0,
	// none				0,			0,				0	};
public:
	Collision(Object* first, Object* second);
	Collision(std::pair<Object*, Object*> objects);
	~Collision();
	bool collision_detector();

	//accessors
	Collider* get_first();
	Collider* get_second();
	ColliderType get_first_type();
	ColliderType get_second_type();
	Object* get_first_object();
	Object* get_second_object();
	void set_collision_detect(bool first_choise, bool second_choise);
};