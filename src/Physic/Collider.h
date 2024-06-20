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
	/// <summary>
	/// ���� �� ��������������� ���������
	/// </summary>
	bool collision_is_detect = false;

	bool has_impulse = false; // ���� �� �������

	Collider(ColliderType collider_type, bool has_impulse);
	~Collider();

	Collider() = delete;
};