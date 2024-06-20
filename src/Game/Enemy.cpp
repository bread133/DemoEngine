#include "Enemy.h"

Enemy::Enemy(std::string name, Model* model, glm::vec3 position, glm::vec3 scale, float speed, float hp, float distance, bool has_impulse, bool has_weapon) :
	Object(name, model, position, scale, glm::vec3(speed), glm::vec3(1.0f), 1.0f, PARALLELEPIPED, ENEMY, has_impulse),
	hp(hp),
	distance(glm::vec3(distance)),
	has_weapon(has_weapon)
{
	is_living = true;
}

Enemy::Enemy(std::string name, Model* model, glm::vec3 position, bool has_impulse, bool has_weapon) :
	Object(name, model, position, glm::vec3(1.0f), glm::vec3(SPEED_ENEMY), glm::vec3(1.0f), 1.0f, PARALLELEPIPED, ENEMY, has_impulse),
	hp(HP),
	distance(DISTANCE),
	has_weapon(has_weapon)
{
	is_living = true;
}

Enemy::~Enemy()
{
}

void Enemy::set_position(Camera* camera, float delta_time)
{
	if(this->has_weapon)
	{

	}
	else
		position += (camera->get_position() - position) * velosity * delta_time;
	// std::cout << position.x << ' ' << position.y << ' ' << position.z << std::endl;
	this->collider->collision_is_detect = false;
}

void Enemy::set_hard_position(Camera* camera, float delta_time, std::vector<glm::vec3>& hard_position)
{
	if (!hard_position.empty())
	{
		position += (hard_position.front() - position) * velosity * delta_time;
		if (position == hard_position.front())
		{
			auto itr = std::find(hard_position.begin(), hard_position.end(), hard_position.front());
			if (itr == hard_position.end())
				return;
			hard_position.erase(itr);
		}
	}
}

bool Enemy::get_is_living()
{
	return is_living;
}

void Enemy::draw(Shader* shader, Window* window, Camera* camera, float delta_time)
{
	if (!has_weapon)
	{
		std::vector<glm::vec3> hard_positions = std::vector<glm::vec3>();
		hard_positions.push_back(glm::vec3(10.0f, 0.0f, 0.0f));
		hard_positions.push_back(glm::vec3(0.0f, 0.0f, 10.0f));
		hard_positions.push_back(glm::vec3(0.0f));

		set_hard_position(camera, delta_time, hard_positions);
	}
	else
		set_position(camera, delta_time);
	Object::draw(shader, window, camera, delta_time);
}

void Enemy::collider_solver(Object* object)
{
	switch (object->get_object_type()) 
	{
	case BULLET:
		this->hp -= ((Bullet*)object)->damage;
		if (hp <= 0) 
		{
			this->is_living = false;
		}
		object->is_living = false;
		break;
	case ENEMY:
		break;
	case SCENE:
		break;
	}
}