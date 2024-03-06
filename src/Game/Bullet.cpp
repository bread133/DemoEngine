#include "Bullet.h"

Bullet::Bullet(Model* model, glm::vec3 position, glm::vec3 scale, float speed, float length) :
	Object(model, position, scale),
	speed(speed),
	length(length)
{
	alive = true;
}

Bullet::~Bullet()
{
	delete model;
}

void Bullet::draw(Shader* shader)
{
	if (alive)
	{
		
	}
}

void Bullet::get_position()
{
	if (alive) 
	{

	}
}

