#include "Bullet.h"

Bullet::Bullet(Model* model, glm::vec3 position, glm::vec3 scale, float speed, float length) :
	Object(model, position, scale),
	speed(speed),
	length(length),
	start_position(position),
	is_living(true)
{
}

Bullet::~Bullet()
{
	delete model;
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

bool Bullet::get_is_living()
{
	return is_living;
}
