#pragma once

#include <src/Render/Graphic/Light.h>

#include <src/Game/Object.h>
#include <src/Game/Enemy.h>
#include <src/Game/Bullet.h>

#include <src/Physic/CollisionSolver.h>

#include <src/Debug/FileHandler.h>

class Map
{
	std::vector<Object*> objects;
	std::vector<LightPoint*> light_points;
	void collision_detector(Object* first);
	Player* player;
	float width;
	float height;
	float depth;
	int enemy_count;

	Bullet* bullet;
	Collider* bullet_collider;
public:
	glm::vec3 gravity = glm::vec3(0.0f, -0.1f, 0.0f); // ускорение свободного падения

	Map(Player* player);
	~Map();
	void add_object(Object* object);
	void remove_object(Object* object);

	void add_light(LightPoint* light);
	void remove_light(LightPoint* light);

	void set_room_parameters(float width, float height, float depth);
	float get_width();
	float get_height();
	float get_depth();
	void gravity_step(Object* object, float delta_time);
	void load();
	Object* back_object();
	void draw(Shader* object_shader, Window* window, Camera* camera, float delta_time); 

	void add_bullet(Window* window, Camera* camera);
	void load_bullet(bool has_impulse);
	void add_bullet_for_enemy(glm::vec3 position);
};