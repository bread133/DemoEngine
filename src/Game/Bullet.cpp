#include "Bullet.h"

Bullet::Bullet(Model* model, glm::vec3 position, glm::vec3 scale, float speed, float length) :
	Object(model, position, scale),
	speed(speed),
	length(length),
	start_position(position),
	is_living(true)
{
}

Bullet::Bullet(Bullet* bullet) :
	Object(bullet->model, bullet->position, bullet->scale),
	speed(bullet->speed),
	length(bullet->length),
	start_position(bullet->position),
	is_living(bullet->is_living)
{
}

Bullet::~Bullet()
{
}

void Bullet::set_position(Camera* camera, float delta_time)
{
	position += camera->get_direction() * speed * delta_time;
}

void Bullet::draw(Shader* shader, Window* window, Camera* camera, float delta_time)
{
	set_position(camera, delta_time);
	Object::draw(shader, window, camera, delta_time);
}

void Bullet::set_start_position(Camera* camera)
{
	position = glm::vec3(camera->get_position().x, 
		camera->get_position().y - 0.5f, camera->get_position().z);
}

bool Bullet::get_is_living()
{
	return is_living;
}
