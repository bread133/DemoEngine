#include "Collision.h"

bool Collision::parallelepiped_parallelepiped()
{
	// текущая позиция в пространстве
	glm::vec3 first_diff = position_first - first->center;
	glm::vec3 second_diff = position_second - second->center;

	glm::vec3 f_cur_max_pos = first_diff + first->collision_points.max_point;
	glm::vec3 f_cur_min_pos = first_diff + first->collision_points.min_point;
	glm::vec3 s_cur_max_pos = second_diff + second->collision_points.max_point;
	glm::vec3 s_cur_min_pos = second_diff + second->collision_points.min_point;

	return (
		f_cur_min_pos.x <= s_cur_max_pos.x &&
		f_cur_max_pos.x >= s_cur_min_pos.x &&
		f_cur_min_pos.y <= s_cur_max_pos.y &&
		f_cur_max_pos.y >= s_cur_min_pos.y &&
		f_cur_min_pos.z <= s_cur_max_pos.z &&
		f_cur_max_pos.z >= s_cur_min_pos.z);
}

bool Collision::sphere_sphere()
{
	glm::vec3 first_diff = position_first - first->center;
	glm::vec3 second_diff = position_second - second->center;

	float distance = glm::length(first_diff - second_diff);

	return (
		distance <= first->collision_points.max_point.x 
		+ second->collision_points.max_point.x ||
		distance <= first->collision_points.max_point.y
		+ second->collision_points.max_point.y ||
		distance <= first->collision_points.max_point.z
		+ second->collision_points.max_point.z);
}

bool Collision::parallelepiped_sphere()
{
	glm::vec3 first_diff = position_first - first->center; // first->parallelepiped
	glm::vec3 second_diff = position_second - second->center; // second->sphere

	glm::vec3 f_cur_max_pos = first_diff + first->collision_points.max_point;
	glm::vec3 f_cur_min_pos = first_diff + first->collision_points.min_point;

	float x = glm::max(f_cur_min_pos.x, glm::min(second_diff.x, f_cur_max_pos.x));
	float y = glm::max(f_cur_min_pos.y, glm::min(second_diff.y, f_cur_max_pos.y));
	float z = glm::max(f_cur_min_pos.z, glm::min(second_diff.z, f_cur_max_pos.z));

	float distance = glm::length(glm::vec3(x, y, z) - second_diff);

	return distance < second->collision_points.max_point.x ||
		distance < second->collision_points.max_point.y ||
		distance < second->collision_points.max_point.z;
}

Collision::Collision(Object* first, Object* second)
{
	// этот конструктор нужен, чтобы параллелепипед всегда был 
	// first, если коллизия происходит между параллелепипедом и сферой
	switch (first->collider->collider_type)
	{
	case PARALLELEPIPED:
		this->first = first->collider;
		this->position_first = first->position;
		this->second = second->collider;
		this->position_second = second->position;
		break;
	case SPHERE:
		this->first = second->collider;
		this->position_first = second->position;
		this->second = first->collider;
		this->position_second = first->position;
		break;
	default:
		throw("Некорректный тип фигуры. вычисление коллизии не представляется возможным.");
	}
}

Collision::Collision(std::pair<Object*, Object*> objects)
{
	Collision(objects.first, objects.second);
}

Collision::~Collision()
{
	delete first;
	delete second;
}

bool Collision::collision_detector()
{
	int mask = first->collider_type | second->collider_type;
	// использую тут побитовую маску, так как в ином случае ошибка 
	// компиляции, да и выглдядит локанично
	switch (mask)
	{
	case SPHERE | SPHERE:
		return sphere_sphere();
	case SPHERE | PARALLELEPIPED:
		return parallelepiped_sphere();
	case PARALLELEPIPED | PARALLELEPIPED:
		return parallelepiped_parallelepiped();
	case NONE | NONE:
	case NONE | SPHERE:
	case NONE | PARALLELEPIPED:
		return false;
	default:
		throw("Есть необработанные коллизии. ГГ");
	}
}
