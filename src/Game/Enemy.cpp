#include "Enemy.h"

Enemy::Enemy(Model* model, glm::vec3 position, glm::vec3 scale, float speed, float damage, float hp, float distance) :
	Object(model, position, scale),
	speed(speed),
	damage(damage),
	hp(hp),
	distance(distance)
{
	alive = true;
}

Enemy::Enemy(Model* model, glm::vec3 position) :
	Object(model, position),
	speed(SPEED_ENEMY),
	damage(DAMAGE),
	hp(HP),
	distance(DISTANCE)
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
	glm::vec3 diff = goal - position;

	// OX
	if(glm::abs(diff.x) > distance)
	{
		if (goal.x > 0 && diff.x < 0)
			position.x -= speed * delta_time;
		if (goal.x > 0 && diff.x > 0)
			position.x += speed * delta_time;

		if (goal.x < 0 && diff.x > 0)
			position.x += speed * delta_time;
		if (goal.x < 0 && diff.x < 0)
			position.x -= speed * delta_time;
	}

	// OY
	if (goal.y > 0 && diff.y < 0)
		position.y -= speed * delta_time;
	if (goal.y > 0 && diff.y > 0)
		position.y += speed * delta_time;

	if (goal.y < 0 && diff.y > 0)
		position.y += speed * delta_time;
	if (goal.y < 0 && diff.y < 0)
		position.y -= speed * delta_time;

	// OZ
	if (glm::abs(diff.z) > distance)
	{
		if (goal.z > 0 && diff.z < 0)
			position.z -= speed * delta_time;
		if (goal.z > 0 && diff.z > 0)
			position.z += speed * delta_time;

		if (goal.z < 0 && diff.z > 0)
			position.z += speed * delta_time;
		if (goal.z < 0 && diff.z < 0)
			position.z -= speed * delta_time;
	}
}

void Enemy::draw(Shader* shader, Window* window, Camera* camera, float delta_time)
{
	if (alive)
	{
		get_position(camera, delta_time);
		Object::draw(shader, window, camera);
	}
	else
		delete this;
}

void Enemy::is_dead() 
{
	if (hp == 0)
		alive = false;
}