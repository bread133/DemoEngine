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
/// ����� ���������.
/// </summary>
class Enemy : public Object
{
	/// <summary>
	/// �������� �����.
	/// </summary>
	float speed;
	/// <summary>
	/// ����, ��������� ������.
	/// </summary>
	float damage;
	/// <summary>
	/// ��� ����������� ��������.
	/// </summary>
	signed int hp;
	/// <summary>
	/// �������� �� ����������� ������.
	/// </summary>
	bool is_living;
	/// <summary>
	/// ��������� ����� ������ � �������, 
	/// ������� ���������� � ������ get_position().
	/// </summary>
	float distance;
	/// <summary>
	/// ����� �������.
	/// ��� ��� ������������� �� �����, �� ����.
	/// ���� ����� ������ �������.
	/// </summary>
	/// <param name="camera"></param>
	/// <param name="delta_time"></param>
	void set_position(Camera* camera, float delta_time);
	/// <summary>
	/// ������ �������� is_alive �� false.
	/// </summary>
	void is_dead();
public:
	/// <summary>
	/// �����������.
	/// </summary>
	/// <param name="model">- �������� ���������</param>
	/// <param name="position">- ������� ���������</param>
	/// <param name="scale">- ������ ���������</param>
	/// <param name="speed">- �������� �����</param>
	/// <param name="damage">- ����, ��������� ������</param>
	/// <param name="hp">- ��� ����������� ��������</param>
	/// <param name="distance">- ��������� ����� ������ � �������, ������� ���������� � ������ get_position()</param>
	Enemy(Model* model, glm::vec3 position, glm::vec3 scale, float speed, float damage, float hp, float distance);
	/// <summary>
	/// �����������.
	/// </summary>
	/// <param name="model">- �������� ���������</param>
	/// <param name="position">- ������� ���������</param>
	Enemy(Model* model, glm::vec3 position);
	/// <summary>
	/// ����������.
	/// </summary>
	~Enemy();
	/// <summary>
	/// ������ ��� ��������, ����� �� ������ ���������.
	/// </summary>
	/// <returns>���� �����, �� true, � �������� ������ - false</returns>
	bool get_is_living();
	void draw(Shader* shader, Window* window, Camera* camera, float delta_time);
};