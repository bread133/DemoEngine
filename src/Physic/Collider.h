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
	// ��� ����� ���� ��� ������, ��� � ������������ �����
	glm::vec3 max_point;
	// ���� ��� SphereCollider, �� ��� 0
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