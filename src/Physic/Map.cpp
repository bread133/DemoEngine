#include "Map.h"

void Map::collision_detector(Object* first)
{
	for (Object* second : objects)
	{
		if (first == second || first->collider->collider_type == NONE || second->collider->collider_type == NONE)
			continue;

		Collision* test = new Collision(first, second);
		std::string path = "C://Users/bread/source/repos/DemoEngineWithCMake/src/Debug/log.txt";
		// TODO: логи, господи прости

		if (test->collision_detector())
		{
			CollisionSolver::Solve(first, second);
		}
	}
}

Map::Map(Player* player) :
	player(player)
{
	enemy_count = 0;
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

void Map::add_light(LightPoint* light)
{
	light_points.push_back(light);
}

void Map::remove_light(LightPoint* light)
{
	if (!light)
		return;
	auto itr = std::find(light_points.begin(), light_points.end(), light);
	if (itr == light_points.end())
		return;
	light_points.erase(itr);
}

void Map::set_room_parameters(float width, float height, float depth)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
}

float Map::get_width()
{
	return this->width;
}

float Map::get_height()
{
	return this->height;
}

float Map::get_depth()
{
	return this->depth;
}

// гравитация 
// TODO: добавить в класс булевое свойство, есть 
// ли гравитация у предмета или нет
void Map::gravity_step(Object* object, float delta_time)
{
		object->force += object->mass * gravity;
		object->velosity += object->force / object->mass * delta_time;
		object->position += object->velosity * delta_time;

		object->force = glm::vec3(0.0f);
}

void Map::load()
{
	for (Object* object : objects)
	{
		object->load();
		if (object->collider->collider_type == ENEMY)
			enemy_count++;
	}
}

Object* Map::back_object()
{
	return objects.back();
}

void Map::draw(Shader* object_shader, Window* window, 
	Camera* camera, float delta_time)
{
	for (Object* object : objects)
	{
		collision_detector(object);
		
		// gravity_step(object, delta_time);
		if (!object->is_living) 
		{
			if (object->collider->collider_type == ENEMY)
				enemy_count--;
			remove_object(object);
		}
		else 
		{
			object->draw(object_shader, window, camera, delta_time);
		}
	}
}

void Map::load_bullet(bool has_impulse)
{
	bullet = new Bullet("bullet", new Model(
		"C://Users/bread/source/repos/DemoEngineWithCMake/src/Render/Resources/Models/golf_ball/model.obj",
		false), glm::vec3(0.0f), glm::vec3(1.0f), 5.0f, 10.0f, player->get_damage(), has_impulse);
	bullet->load();
	bullet_collider = bullet->load_sphere_parameters(bullet, has_impulse);
	FileHandler::write_line_collider_parameters(bullet_collider);
}

void Map::add_bullet_for_enemy(glm::vec3 position)
{
	bullet->set_start_position(position);
	this->add_object(new Bullet(bullet));
	this->back_object()->load();
	this->back_object()->collider = bullet_collider;
}

void Map::add_bullet(Window* window, Camera* camera)
{
	bullet->set_start_position(camera);
	this->add_object(new Bullet(bullet));
	this->back_object()->load();
	this->back_object()->collider = bullet_collider;
}
