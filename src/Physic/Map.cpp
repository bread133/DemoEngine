#include "Map.h"

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
