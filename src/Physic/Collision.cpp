#include "Collision.h"

const float margin = 0.5f; // чтобы пересечений по факту не было

bool Collision::sphere_sphere_collision(Object* first, Object* second)
{
	SphereCollider first_c = first->get_collider();
	SphereCollider second_c = second->get_collider();

	return false;
}

bool Collision::intersect_sphere_parallelepiped(ParallelepipedCollider pc, 
	glm::vec3 pos_pc, SphereCollider sc, glm::vec3 pos_sc)
{
	return false;
}

bool Collision::sphere_parallelepiped_collision(Object* first, Object* second)
{
	switch (first->get_collider().collider_type) 
	{
	case SPHERE:
		SphereCollider first_cs = first->get_collider();
		ParallelepipedCollider second_cs = second->get_collider();

		return intersect_sphere_parallelepiped(second_cs, second->position,
			first_cs, first->position);
	case PARALLELEPIPED:
		ParallelepipedCollider first_cp = first->get_collider();
		SphereCollider second_cp = second->get_collider();

		return intersect_sphere_parallelepiped(first_cp, first->position,
			second_cp, second->position);
	default:
		throw("Быть того не может!");
	}
}

bool Collision::parallelepiped_parallelepiped_collision(Object* first, Object* second)
{
	ParallelepipedCollider first_c = first->get_collider();
	ParallelepipedCollider second_c = second->get_collider();

	// текущая позиция в пространстве
	glm::vec3 f_cur_max_pos = first_c.center - first->position + first_c.max_point + margin;
	glm::vec3 f_cur_min_pos = first_c.center - first->position + first_c.min_point - margin;
	glm::vec3 s_cur_max_pos = second_c.center - second->position + second_c.max_point + margin;
	glm::vec3 s_cur_min_pos = second_c.center - second->position + second_c.min_point - margin;

	return (
		f_cur_min_pos.x <= s_cur_max_pos.x &&
		f_cur_max_pos.x >= s_cur_min_pos.x &&
		f_cur_min_pos.y <= s_cur_max_pos.y &&
		f_cur_max_pos.y <= s_cur_min_pos.y &&
		f_cur_min_pos.z <= s_cur_max_pos.z &&
		f_cur_max_pos.z <= s_cur_min_pos.z
		);
}

bool Collision::collision_detector(Object* first, Object* second)
{
	int mask = first->get_collider().collider_type | second->get_collider().collider_type;

	// использую тут побитовую маску, так как в ином случае ошибка 
	// компиляции
	switch (mask)
	{
	case SPHERE | SPHERE:
		return sphere_sphere_collision(first, second);
	case SPHERE | PARALLELEPIPED:
		return sphere_parallelepiped_collision(first, second);
	case PARALLELEPIPED | PARALLELEPIPED:
		return parallelepiped_parallelepiped_collision(first, second);
	case NONE | NONE:
	case NONE | SPHERE:
	case NONE | PARALLELEPIPED:
		return false;
	};
	return false;
}

bool Collision::collision_detector(std::pair<Object*, Object*> objects)
{
	return collision_detector(objects.first, objects.second);
}
