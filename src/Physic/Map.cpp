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

void Map::step(float delta_time)
{

}
