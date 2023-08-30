#include "Enemy.h"

Enemy::Enemy(Model* model, float pos_x, float pos_y, float pos_z, float speed, float damage, float hp) :
	model(model),
	speed(speed),
	position(glm::vec3(pos_x, pos_y, pos_z)),
	damage(damage),
	hp(hp)
{
	alive = true;
}

Enemy::Enemy(Model* model, float pos_x, float pos_y, float pos_z) :
	model(model),
	position(glm::vec3(pos_x, pos_y, pos_z)),
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

void Enemy::draw(Shader* shader)
{
	model->draw(shader);
}