#include "CollisionSolver.h"

void CollisionSolver::Solve(Object* first, Object* second)
{
	std::cout << "COLLISION DETECT BETWEEN" << ": " << first->collider->collider_type << "(" << first->get_name()
		<< ") AND " << second->collider->collider_type << "(" << first->get_name() << ")" << std::endl;

	if (first->collider->collider_type && second->collider->collider_type != (NONE | NONE))
	{
		first->collider->collision_is_detect = true;
		second->collider->collision_is_detect = true;

		first->collider_solver(second);
		second->collider_solver(first);
	}
}