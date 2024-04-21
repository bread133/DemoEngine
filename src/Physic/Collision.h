#pragma once
#include "Collider.h"
#include "../Game/Object.h"

#include <utility>
#include <glm/vec3.hpp>
#include <string>


const float MARGIN = 0.5f;

class Collision
{
	Collider* first;
	glm::vec3 position_first;
	Collider* second;
	glm::vec3 position_second;

	bool parallelepiped_parallelepiped();
	bool sphere_sphere();
	bool parallelepiped_sphere();

	// const int* table_of_collide = new int[]{
					// sphere	paral-ed			none
	// sphere			1,			1,				0,
	//paral - ed		1,			1,				0,
	// none				0,			0,				0	};
public:
	Collision(Object* first, Object* second);
	Collision(std::pair<Object*, Object*> objects);
	~Collision();
	bool collision_detector();
};