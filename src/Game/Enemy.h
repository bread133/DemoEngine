#pragma once
#include "../Render/Graphic/Model.h"
#include "../Render/Graphic/Shader.h"
#include "Object.h"
#include "../Render/Window.h"
#include "../Render/Graphic/Camera.h"

#include <glm/vec3.hpp>
#include <vector>

const float			SPEED_ENEMY = 1.5f;
const float			DAMAGE = 5.0f;
const int			HP = 100.0f;
const float			DISTANCE = 3.0f;

/// <summary>
/// класс соперника.
/// </summary>
class Enemy : public Object
{
	/// <summary>
	/// скорость врага.
	/// </summary>
	float speed;
	/// <summary>
	/// урон, наносимый игроку.
	/// </summary>
	float damage;
	/// <summary>
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
	float distance;
	/// <summary>
	/// смена позиции.
	/// вот тут прописывается ии врага, по идее.
	/// пока здесь просто затычка.
	/// </summary>
	/// <param name="camera"></param>
	/// <param name="delta_time"></param>
	void set_position(Camera* camera, float delta_time);
	/// <summary>
	/// меняет значение is_alive на false.
	/// </summary>
	void is_dead();
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
	Enemy(Model* model, glm::vec3 position, glm::vec3 scale, float speed, float damage, float hp, float distance);
	/// <summary>
	/// конструктор.
	/// </summary>
	/// <param name="model">- моделька соперника</param>
	/// <param name="position">- позиция соперника</param>
	Enemy(Model* model, glm::vec3 position);
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
};