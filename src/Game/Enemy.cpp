#include "Enemy.h"

Enemy::Enemy(Model* model, float pos_x, float pos_y, float pos_z, float speed, float damage, float hp) :
	Object(model, pos_x, pos_y, pos_z),
	speed(speed),
	damage(damage),
	hp(hp)
{
	alive = true;
}

Enemy::Enemy(Model* model, float pos_x, float pos_y, float pos_z) :
	Object(model, pos_x, pos_y, pos_z),
	speed(SPEED_ENEMY),
	damage(DAMAGE),
	hp(HP)
{
	alive = true;
}

Enemy::~Enemy()
{
	delete model;
}

void Enemy::get_position(Camera* camera, float delta_time)
{
	glm::vec3 goal = camera->get_position();
	position += goal * delta_time * speed;
}

void Enemy::draw(Shader* shader, int WIDTH, int HEIGHT, Camera* camera)
{
	if (alive)
	{
		camera->mvp_transformation(WIDTH, HEIGHT, shader, position);
		Object::draw(shader);
	}
}

void Enemy::is_dead() 
{
	if (hp == 0)
		alive = false;
}