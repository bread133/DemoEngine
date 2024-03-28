#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::add_object(Object* object)
{
	objects.push_back(object);
}

void Map::remove_object(Object* object)
{
	if (!object)
		return;
	auto itr = std::find(objects.begin(), objects.end(), object);
	if (itr == objects.end())
		return;
	objects.erase(itr);
}

// гравитация 
// TODO: добавить в класс булевое свойство, есть 
// ли гравитация у предмета или нет
void Map::gravity_step(Object* object, float delta_time)
{
		object->force += object->mass * gravity;
		object->velosity += object->force /
			object->mass * delta_time;
		object->position += object->velosity * delta_time;

		object->force = glm::vec3(0.0f);
}

void Map::load()
{
	for (Object* object : objects)
	{
		object->load();
	}
}

Object* Map::back_object()
{
	return objects.back();
}

void Map::draw(Shader* object_shader, Window* window, 
	Camera* camera, float delta_time)
{
	// collision_detector();

	for (Object* object : objects)
	{
		object->draw(object_shader, window, camera, delta_time);
		// gravity_step(object, delta_time);
	}
}
