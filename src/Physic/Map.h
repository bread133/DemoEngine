#pragma once
#include "src/Game/Object.h"

class Map
{
	std::vector<Object*> objects;
	glm::vec3 gravity = glm::vec3(0.0f, -9.8f, 0.0f); // ускорение свободного падения
public:
	Map();
	~Map();
	void add_object(Object* object);
	void remove_object(Object* object);
	void step(float delta_time);
};