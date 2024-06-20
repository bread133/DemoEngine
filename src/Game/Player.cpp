#include "Player.h"

Player::Player(Camera* camera)
{
	Player(camera, MARGIN_PLAYER, DAMAGE_PLAYER, HP_PLAYER);
}

Player::Player(Camera* camera, glm::vec3 margin, float damage, float hp) :
	camera(camera),
	margin(margin),
	damage(damage),
	hp(hp)
{
	if (margin.x < 0 || margin.y < 0 || margin.z < 0)
		throw "√раница главного игрока не может быть меньше нул€";
	if (damage < 0)
	{
		std::string error_message = "Ќаносимый урон должен быть больше нул€";
		throw(error_message);
	}
	collider = new Collider(PARALLELEPIPED, false);
	collider->center = camera->get_position();
	collider->collision_points.max_point = margin;
	collider->collision_points.min_point = -margin;
}

float Player::get_damage()
{
	return this->damage;
}
