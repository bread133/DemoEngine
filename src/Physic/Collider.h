#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

enum ColliderType
{
	SPHERE = 1,
	PARALLELEPIPED = 2,
	NONE = 4,
};

struct CollisionPoints
{
	// это может быть как радиус, так и максимальная точка
	glm::vec3 max_point;
	// если это SphereCollider, то тут 0
	glm::vec3 min_point;
};

struct Collider
{
	ColliderType collider_type;
	glm::vec3 center;
	CollisionPoints collision_points;

	Collider(ColliderType collider_type);
	~Collider();

	Collider() = delete;
};