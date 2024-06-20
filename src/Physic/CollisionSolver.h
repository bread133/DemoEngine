#pragma once

#include <iostream>

#include <src/Game/Player.h>

#include <src/Physic/Collision.h>

class CollisionSolver 
{
public:
	static void Solve(Object* first, Object* second);
};