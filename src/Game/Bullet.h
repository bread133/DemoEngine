#pragma once
#include "src/Render/Graphic/Shader.h"
#include "src/Game/Object.h"

#include <string>

/// <summary>
/// класс выстрелов
/// </summary>
class Bullet final : public Object
{
	glm::vec3 start_position;
	float length;
	void set_position(Camera* camera, float delta_time);
public:
	float damage;
	Bullet(std::string name, Model* model, glm::vec3 position, glm::vec3 scale, float speed, float length, float damage, bool has_impulse);
	Bullet(Bullet* bullet);
	~Bullet();

	void set_start_position(Camera* camera);
	void set_start_position(glm::vec3 position);
	void set_position(glm::vec3 position, float delta_time);
	void load();
	void draw(Shader* shader, Window* window, Camera* camera, float delta_time);
	void collider_solver(Object* object) override;
};