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
	/// <summary>
	/// длина выстрела.
	/// </summary>
	float length;
	/// <summary>
	/// отображение выстрела.
	/// </summary>
	bool is_living;
	void set_position(Camera* camera, float delta_time);
public:
	/// <summary>
	/// конструктор.
	/// </summary>
	/// <param name="model">- моделька соперника</param>
	/// <param name="position">- позиция соперника</param>
	/// <param name="scale">- размер соперника</param>
	/// <param name="speed">- скорость врага</param>
	/// <param name="length">- длина выстрела</param>
	Bullet(std::string name, Model* model, glm::vec3 position, glm::vec3 scale, float speed, float length);
	Bullet(Bullet* bullet);
	/// <summary>
	/// деструктор.
	/// </summary>
	~Bullet();
	/// <summary>
	/// 
	/// </summary>
	/// <returns>если разница между стартом и текущей точкой больше, 
	/// то false</returns>
	bool get_is_living();
	void set_start_position(Camera* camera);
	void load();
	void draw(Shader* shader, Window* window, Camera* camera, float delta_time);
};