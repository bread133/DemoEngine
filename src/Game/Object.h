#pragma once

#include "../Render/Graphic/Model.h"
#include "../Render/Graphic/Shader.h"
#include "../Render/Window.h"
#include "../Render/Graphic/Camera.h"
#include "src/Physic/Collider.h"

#include <vector>
#include <string>

const int NAME_LENGTH = 20;

class Object
{
protected:
	glm::vec3 scale;
	Model* model;
	// коллизии
	ColliderType collider_type;
	Collider collider;

	void load_collision_parameters();
	ParallelepipedCollider load_parallelepiped_parameters();
	SphereCollider load_sphere_parameters();
	std::pair<glm::vec3, glm::vec3> get_min_max();
public:
	glm::vec3 position;			// позиция
	glm::vec3 velosity;			// скорость
	glm::vec3 force;			// сила удара
	float mass;					// масса

	Object(Model* model, glm::vec3 position, glm::vec3 scale,
		glm::vec3 velosity, glm::vec3 force, float mass, ColliderType type);
	Object(std::string name, Model* model, glm::vec3 position, glm::vec3 scale, ColliderType type);
	~Object();
	virtual void load();
	virtual void draw(Shader* shader, Window* window, Camera* camera, float delta_time);

	std::string get_name();
	
	inline SphereCollider load_sphere_parameters(Object* object);
	inline ParallelepipedCollider load_parallelepiped_parameters(Object* object);
};