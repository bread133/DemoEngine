#include "Bullet.h"

Bullet::Bullet(std::string name, Model* model, glm::vec3 position, glm::vec3 scale, float speed, float length) :
	Object(name, model, position, scale, glm::vec3(speed), glm::vec3(0.0f), 1.0f, SPHERE),
	length(length),
	start_position(position),
	is_living(true)
{
}

Bullet::Bullet(Bullet* bullet) :
	Object(bullet->name, bullet->model, bullet->position, bullet->scale, 
		bullet->velosity, bullet->force, bullet->mass, SPHERE),
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
	position += camera->get_direction() * velosity * delta_time;
	// std::cout << position.x << ' ' << position.y << ' ' << position.z << std::endl;
}

void Bullet::draw(Shader* shader, Window* window, Camera* camera, float delta_time)
{
	set_position(camera, delta_time);
	Object::draw(shader, window, camera, delta_time);
}

void Bullet::set_start_position(Camera* camera)
{
	position = camera->get_position() - glm::vec3(0.0f, 0.5f, 0.0f);
}

bool Bullet::get_is_living()
{
	return is_living;
}

void Bullet::load()
{
	model->load_model();
	// лог
	FileHandler::write_line_load_object(name);
}