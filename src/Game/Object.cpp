#include "Object.h"

void Object::load_collision_parameters()
{
	switch (collider_type)
	{
	case SPHERE:
		collider = load_sphere_parameters(has_impulse);
		break;
	case PARALLELEPIPED:
		collider = load_parallelepiped_parameters(has_impulse);
		break;
	case NONE:
		collider = new Collider(NONE, has_impulse);
		break;
	default:
		throw("Не указан тип коллизии.");
	}
}

std::pair<glm::vec3, glm::vec3> Object::get_min_max()
{
	glm::vec3 min = model->mesh->vertices[0].position;
	glm::vec3 max = min;
	for (Vertex value : model->mesh->vertices)
	{
		min.x = value.position.x < min.x ? value.position.x : min.x;
		min.y = value.position.y < min.y ? value.position.y : min.y;
		min.z = value.position.z < min.z ? value.position.z : min.z;

		max.x = value.position.x > max.x ? value.position.x : max.x;
		max.y = value.position.y > max.y ? value.position.y : max.y;
		max.z = value.position.z > max.z ? value.position.z : max.z;
	}

	return std::pair<glm::vec3, glm::vec3>(min, max);
}

Collider* Object::load_sphere_parameters(bool has_impulse)
{
	return Object::load_sphere_parameters(this, has_impulse);
}

Collider* Object::load_parallelepiped_parameters(bool has_impulse)
{
	return Object::load_parallelepiped_parameters(this, has_impulse);
}

Object::Object(std::string name, Model* model, glm::vec3 position, glm::vec3 scale,
	ColliderType type, ObjectType object_type, bool has_impulse) :
	model(model),
	position(position),
	scale(scale),
	velosity(glm::vec3(0.0f)),
	force(glm::vec3(0.0f)),
	mass(0.0f),
	collider_type(type),
	object_type(object_type),
	has_impulse(has_impulse)
{
	if (name.size() >= NAME_LENGTH)
	{
		std::string error_message = "Превышена длина названия строки. Имя должно содержать "
			+ NAME_LENGTH;
		throw(error_message);
	}
	this->name = name;
	this->is_living = true;
}

Object::Object(std::string name, Model* model, glm::vec3 position, glm::vec3 scale, 
	glm::vec3 velosity, glm::vec3 force, float mass, ColliderType type, ObjectType object_type, 
	bool has_impulse) :
	model(model),
	position(position),
	scale(scale),
	velosity(velosity),
	force(force),
	mass(mass),
	collider_type(type),
	object_type(object_type),
	has_impulse(has_impulse)
{
	if (name.size() >= NAME_LENGTH)
	{
		std::string error_message = "Превышена длина названия строки. Имя должно содержать "
			+ NAME_LENGTH;
		throw(error_message);
	}
	this->name = name;
	this->is_living = true;
}

Object::~Object()
{
	delete model;
}

void Object::load()
{
	model->load_model();
	// коллайдеры
	load_collision_parameters();
	// логи
	FileHandler::write_line_load_object(name);
	FileHandler::write_line_collider_parameters(collider);
}

void Object::draw(Shader* shader, Window* window, Camera* camera, float delta_time)
{
	camera->mvp_transformation(window, shader, position, scale);
	model->draw(shader);
}

void Object::collider_solver(Object* object)
{
}

std::string Object::get_name()
{
	return name;
}

ObjectType Object::get_object_type()
{
	return object_type;
}

Collider* Object::load_sphere_parameters(Object* object, bool has_impulse)
{
	std::pair<glm::vec3, glm::vec3> min_max = object->get_min_max();
	glm::vec3 min = min_max.first;
	glm::vec3 max = min_max.second;

	Collider* _collider = new Collider(SPHERE, has_impulse);
	_collider->center = (max + min) / 2.0f;
	_collider->collision_points.max_point = 
		object->model->mesh->vertices[0].position - _collider->center;

	return _collider;
}

Collider* Object::load_parallelepiped_parameters(Object* object, bool has_impulse)
{
	std::pair<glm::vec3, glm::vec3> min_max = object->get_min_max();

	Collider* _collider = new Collider(PARALLELEPIPED, has_impulse);
	_collider->collision_points.max_point = min_max.second;
	_collider->collision_points.min_point = min_max.first;
	_collider->center = (min_max.second + min_max.first) / 2.0f;

	return _collider;
}
