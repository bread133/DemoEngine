#include "Object.h"

void Object::load_collision_parameters()
{
	switch (collider_type)
	{
	case SPHERE:
		collider = load_sphere_parameters();
		break;
	case PARALLELEPIPED:
		collider = load_parallelepiped_parameters();
		break;
	case NONE:
		collider = NoneCollider();
		break;
	default:
		throw("�� ������ ��� ��������.");
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

SphereCollider Object::load_sphere_parameters()
{
	return Object::load_sphere_parameters(this);
}

ParallelepipedCollider Object::load_parallelepiped_parameters()
{
	return Object::load_parallelepiped_parameters(this);
}

Object::Object(std::string name, Model* model, glm::vec3 position, glm::vec3 scale,
	glm::vec3 velosity, glm::vec3 force, float mass, ColliderType type) :
	model(model),
	position(position),
	scale(scale),
	velosity(velosity),
	force(force),
	mass(mass),
	collider_type(type)
{
	if (name.size() >= NAME_LENGTH) 
	{
		std::string error_message = "Превышена длина названия строки. Имя должно содержать "
			+ NAME_LENGTH;
		throw(error_message);
}
	this->name = name;
}

Object::Object(std::string name, Model* model, glm::vec3 position, glm::vec3 scale, ColliderType type) :
	model(model),
	position(position),
	scale(scale),
	velosity(glm::vec3(0.0f)),
	force(glm::vec3(0.0f)),
	mass(0.0f),
	collider_type(type)
{
	if (name.size() >= NAME_LENGTH)
	{
		std::string error_message = "Превышена длина названия строки. Имя должно содержать "
			+ NAME_LENGTH;
		throw(error_message);
}
	this->name = name;
}

Object::~Object()
{
	delete model;
}

void Object::load()
{
	model->load_model();
	// ����������
	load_collision_parameters();
}

void Object::draw(Shader* shader, Window* window, Camera* camera, float delta_time)
{
	camera->mvp_transformation(window, shader, position, scale);
	model->draw(shader);
}

Collider Object::get_collider()
{
	return collider;
}

SphereCollider Object::load_sphere_parameters(Object* object)
{
	std::pair<glm::vec3, glm::vec3> min_max = object->get_min_max();
	glm::vec3 min = min_max.first;
	glm::vec3 max = min_max.second;

	SphereCollider _collider = SphereCollider();
	_collider.center = (max - min) / 2.0f;
	_collider.radius = object->model->mesh->vertices[0].position
		- _collider.center;

	return _collider;
}

ParallelepipedCollider Object::load_parallelepiped_parameters(Object* object)
{
	std::pair<glm::vec3, glm::vec3> min_max = object->get_min_max();

	ParallelepipedCollider _collider = ParallelepipedCollider();
	_collider.max_point = min_max.second;
	_collider.min_point = min_max.first;
	_collider.center = (_collider.max_point -
		_collider.min_point) / 2.0f;

	_collider.diff = _collider.max_point - _collider.center;

	return _collider;
}
