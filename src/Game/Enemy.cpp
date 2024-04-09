#include "Enemy.h"

Enemy::Enemy(std::string name, Model* model, glm::vec3 position, glm::vec3 scale, float speed, float damage, float hp, float distance) :
	Object(name, model, position, scale, glm::vec3(speed), glm::vec3(1.0f), 1.0f, PARALLELEPIPED),
	damage(damage),
	hp(hp),
	distance(glm::vec3(distance))
{
	is_living = true;
}

Enemy::Enemy(std::string name, Model* model, glm::vec3 position) :
	Object(name, model, position, scale, glm::vec3(SPEED_ENEMY), glm::vec3(1.0f), 1.0f, PARALLELEPIPED),
	damage(DAMAGE),
	hp(HP),
	distance(DISTANCE)
{
	is_living = true;
}

Enemy::~Enemy()
{
}

void Enemy::set_position(Camera* camera, float delta_time)
{
	position += (camera->get_position() - position) * velosity * delta_time;
	// std::cout << position.x << ' ' << position.y << ' ' << position.z << std::endl;
}

bool Enemy::get_is_living()
{
	return is_living;
}


void Enemy::is_dead() 
{
	if (hp == 0)
		is_living = false;
}

void Enemy::draw(Shader* shader, Window* window, Camera* camera, float delta_time)
{
	set_position(camera, delta_time);
	Object::draw(shader, window, camera, delta_time);
}