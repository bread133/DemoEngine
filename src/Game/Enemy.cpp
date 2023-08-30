#include "Enemy.h"

void Enemy::move()
{
	float min_y = model->mesh->vertices[0].position.y;
	for (int i = 1; i < model->mesh->vertices.size(); i++)
		if (min_y > model->mesh->vertices[i].position.y)
			min_y = model->mesh->vertices[i].position.y;

	std::vector<glm::vec3> down_left_dots;
	for (int i = 0; i < model->mesh->vertices.size(); i++)
		if (min_y == model->mesh->vertices[i].position.y)
			down_left_dots.push_back(model->mesh->vertices[i].position);

	glm::vec3 down_left_dot;
	if (down_left_dots.size() == 1)
		down_left_dot = down_left_dots[0];
	else
	{
		float max_z = down_left_dots[0].z;
		for (int i = 1; i < down_left_dots.size(); i++)
			if (max_z < down_left_dots[i].z)
				max_z = down_left_dots[i].z;
		for(int i = down_left_dots.size() - 1; i > -1; i--)
			if(down_left_dots[i].z != max_z)
				down_left_dots.erase(down_left_dots.begin() + i);

		if (down_left_dots.size() == 1)
			down_left_dot = down_left_dots[0];
		else
		{
			float max_y = down_left_dots[0].y;
			int index = 0;
			for (int i = 1; i < down_left_dots.size(); i++)
				if (max_z < down_left_dots[i].y)
				{
					max_z = down_left_dots[i].y;
					index = i;
				}
			down_left_dot = down_left_dots[index];
		}
	}

	glm::vec3 translation = position - down_left_dot;
	for (int i = 0; i < model->mesh->vertices.size(); i++)
	{
		model->mesh->vertices[i].position -= translation;
	}
}

Enemy::Enemy(Model* model, float pos_x, float pos_y, float pos_z, float speed, float damage, float hp) :
	model(model),
	speed(speed),
	position(glm::vec3(pos_x, pos_y, pos_z)),
	damage(damage),
	hp(hp)
{
	alive = true;
	move();
}

Enemy::Enemy(Model* model, float pos_x, float pos_y, float pos_z) :
	model(model),
	position(glm::vec3(pos_x, pos_y, pos_z)),
	speed(SPEED_ENEMY),
	damage(DAMAGE),
	hp(HP)
{
	alive = true;
	move();
}

Enemy::~Enemy()
{
	delete model;
}

void Enemy::draw(Shader* shader)
{
	model->draw(shader);
}