#pragma once
#include "src/Game/Object.h"

class Map
{
	std::vector<Object*> objects;
public:
	void add_object(Object* object);
	void remove_object(Object* object);
};