#include "Bullet.h"

Bullet::Bullet(std::string name, Model* model, glm::vec3 position, glm::vec3 scale, float speed, float length, float damage, bool has_impulse) :
	Object(name, model, position, scale, glm::vec3(speed), glm::vec3(0.0f), 1.0f, SPHERE, BULLET, has_impulse),
	length(length),
	damage(damage),
	start_position(position)
{
}

Bullet::Bullet(Bullet* bullet) :
	Object(bullet->name, bullet->model, bullet->position, bullet->scale, 
		bullet->velosity, bullet->force, bullet->mass, SPHERE, BULLET, has_impulse),
	length(bullet->length),
	damage(damage),
	start_position(bullet->position)
{
}

Bullet::~Bullet()
{
}

void Bullet::set_position(Camera* camera, float delta_time)
{
	this->position += camera->get_direction() * velosity * delta_time;
	// std::cout << position.x << ' ' << position.y << ' ' << position.z << std::endl;
}

void Bullet::draw(Shader* shader, Window* window, Camera* camera, float delta_time)
{
	length -= delta_time;
	set_position(camera, delta_time);
	Object::draw(shader, window, camera, delta_time);
	if (length < 0)
		Object::is_living = false;
}

void Bullet::collider_solver(Object* object)
{
	switch(object->get_object_type())
	{
	case SCENE:
		this->is_living = false;
		break;
	case ENEMY:
		this->is_living = false;
		object->is_living = false;
		break;
	}
}

void Bullet::set_start_position(Camera* camera)
{
	this->position = camera->get_position() - glm::vec3(0.0f, 0.5f, 0.0f);
}

void Bullet::set_start_position(glm::vec3 position)
{
	this->position = position;
}

void Bullet::set_position(glm::vec3 position, float delta_time)
{
	this->position += position * velosity * delta_time;
}

void Bullet::load()
{
	model->load_model();
	// лог
	FileHandler::write_line_load_object(name);
}