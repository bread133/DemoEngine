#pragma once

#include "src/Render/Graphic/Model.h"
#include "src/Render/Graphic/Shader.h"
#include "src/Render/Window.h"
#include "src/Render/Graphic/Camera.h"

#include "src/Physic/Collider.h"

#include "src/Debug/FileHandler.h"
#include <src/Game/Player.h>

#include <iostream>
#include <vector>
#include <string>

const int NAME_LENGTH = 20;

enum ObjectType
{
	SCENE,
	ENEMY,
	BULLET
};

class Object
{
protected:
	std::string name;
	glm::vec3 scale;
	Model* model;
	// коллизии
	ColliderType collider_type;
	ObjectType object_type;

	void load_collision_parameters();
	Collider* load_parallelepiped_parameters(bool has_impulse);
	Collider* load_sphere_parameters(bool has_impulse);
	std::pair<glm::vec3, glm::vec3> get_min_max();
public:
	bool has_impulse;

	glm::vec3 position;			// позиция
	glm::vec3 velosity;			// скорость
	glm::vec3 force;			// сила удара
	float mass;					// масса
	bool is_living;
	
	Collider* collider;

	Object(std::string name, Model* model, glm::vec3 position, glm::vec3 scale,
		glm::vec3 velosity, glm::vec3 force, float mass, ColliderType type, ObjectType object_type, bool has_impulse);
	Object(std::string name, Model* model, glm::vec3 position, glm::vec3 scale, 
		ColliderType type, ObjectType object_type, bool has_impulse);
	~Object();
	virtual void load();
	virtual void draw(Shader* shader, Window* window, Camera* camera, float delta_time);
	virtual void collider_solver(Object* object);
	
	std::string get_name();
	ObjectType get_object_type();

	inline Collider* load_sphere_parameters(Object* object, bool has_impulse);
	inline Collider* load_parallelepiped_parameters(Object* object, bool has_impulse);
};