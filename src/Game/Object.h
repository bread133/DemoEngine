#pragma once

#include "src/Render/Graphic/Model.h"
#include "src/Render/Graphic/Shader.h"
#include "src/Render/Window.h"
#include "src/Render/Graphic/Camera.h"
#include "src/Physic/Collider.h"
#include "src/Debug/FileHandler.h"

#include <iostream>
#include <vector>
#include <string>

const int NAME_LENGTH = 20;

class Object
{
protected:
	std::string name;
	glm::vec3 scale;
	Model* model;
	// коллизии
	ColliderType collider_type;

	void load_collision_parameters();
	Collider* load_parallelepiped_parameters();
	Collider* load_sphere_parameters();
	std::pair<glm::vec3, glm::vec3> get_min_max();
public:
	glm::vec3 position;			// позиция
	glm::vec3 velosity;			// скорость
	glm::vec3 force;			// сила удара
	float mass;					// масса

	Collider* collider;

	Object(std::string name, Model* model, glm::vec3 position, glm::vec3 scale,
		glm::vec3 velosity, glm::vec3 force, float mass, ColliderType type);
	Object(std::string name, Model* model, glm::vec3 position, glm::vec3 scale, ColliderType type);
	~Object();
	virtual void load();
	virtual void draw(Shader* shader, Window* window, Camera* camera, float delta_time);
	
	std::string get_name();

	inline Collider* load_sphere_parameters(Object* object);
	inline Collider* load_parallelepiped_parameters(Object* object);
};