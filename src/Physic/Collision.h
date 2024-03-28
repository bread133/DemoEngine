#pragma once
#include "Collider.h"
#include "../Game/Object.h"

#include <utility>
#include <glm/vec3.hpp>
#include <string>

class Collision
{
	// const int* table_of_collide = new int[]{
					// sphere	paral-ed			none
	// sphere			1,			1,				0,
	//paral - ed		1,			1,				0,
	// none				0,			0,				0	};

	inline bool sphere_sphere_collision(Object* first, Object* second);
	inline bool sphere_parallelepiped_collision(Object* first, Object* second);
	inline bool parallelepiped_parallelepiped_collision(Object* first, Object* second);
	inline bool intersect_sphere_parallelepiped(ParallelepipedCollider pc,
		glm::vec3 pos_pc, SphereCollider sc, glm::vec3 pos_sc);
public:
	inline bool collision_detector(Object* first, Object* second);
	inline bool collision_detector(std::pair<Object*, Object*> objects);
};