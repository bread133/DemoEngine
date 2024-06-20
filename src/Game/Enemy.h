#pragma once
#include <src/Game/Object.h>
#include <src/Game/Bullet.h>

#include <src/Render/Graphic/Model.h>
#include <src/Render/Graphic/Shader.h>
#include <src/Render/Window.h>
#include <src/Render/Graphic/Camera.h>

#include <glm/vec3.hpp>
#include <vector>

const float			SPEED_ENEMY = 0.5f;
const float			DAMAGE = 5.0f;
const int			HP = 100.0f;
const glm::vec3		DISTANCE = glm::vec3(3.0f);

/// <summary>
/// класс соперника.
/// </summary>
class Enemy : public Object
{
	/// его собственное здоровье.
	/// </summary>
	signed int hp;
	/// <summary>
	/// отвечает за отображение модели.
	/// </summary>
	bool is_living;
	/// <summary>
	/// дистанция между врагом и игроком, 
	/// которая необходима в методе get_position().
	/// </summary>
	glm::vec3 distance;
	/// <summary>
	/// смена позиции.
	/// вот тут прописывается ии врага, по идее.
	/// пока здесь просто затычка.
	/// </summary>
	/// <param name="camera"></param>
	/// <param name="delta_time"></param>
	void set_position(Camera* camera, float delta_time);
	void set_hard_position(Camera* camera, float delta_time, std::vector<glm::vec3>& hard_position);

	bool has_weapon;
	bool has_bost = false;
public:
	/// <summary>
	/// конструктор.
	/// </summary>
	/// <param name="model">- моделька соперника</param>
	/// <param name="position">- позиция соперника</param>
	/// <param name="scale">- размер соперника</param>
	/// <param name="speed">- скорость врага</param>
	/// <param name="damage">- урон, наносимый игроку</param>
	/// <param name="hp">- его собственное здоровье</param>
	/// <param name="distance">- дистанция между врагом и игроком, которая необходима в методе get_position()</param>
	Enemy(std::string name, Model* model, glm::vec3 position, glm::vec3 scale, float speed, float hp, 
		float distance, bool has_impulse, bool has_weapon);
	/// <summary>
	/// конструктор.
	/// </summary>
	/// <param name="model">- моделька соперника</param>
	/// <param name="position">- позиция соперника</param>
	Enemy(std::string name, Model* model, glm::vec3 position, bool has_impulse, bool has_weapon);
	/// <summary>
	/// деструктор.
	/// </summary>
	~Enemy();
	/// <summary>
	/// геттер для значения, живой ли данный экземпляр.
	/// </summary>
	/// <returns>если живой, то true, в обратном случае - false</returns>
	bool get_is_living();
	void draw(Shader* shader, Window* window, Camera* camera, float delta_time);
	void collider_solver(Object* object) override;
};