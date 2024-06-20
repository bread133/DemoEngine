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
/// ����� ���������.
/// </summary>
class Enemy : public Object
{
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
	glm::vec3 distance;
	/// <summary>
	/// ����� �������.
	/// ��� ��� ������������� �� �����, �� ����.
	/// ���� ����� ������ �������.
	/// </summary>
	/// <param name="camera"></param>
	/// <param name="delta_time"></param>
	void set_position(Camera* camera, float delta_time);
	void set_hard_position(Camera* camera, float delta_time, std::vector<glm::vec3>& hard_position);

	bool has_weapon;
	bool has_bost = false;
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
	Enemy(std::string name, Model* model, glm::vec3 position, glm::vec3 scale, float speed, float hp, 
		float distance, bool has_impulse, bool has_weapon);
	/// <summary>
	/// �����������.
	/// </summary>
	/// <param name="model">- �������� ���������</param>
	/// <param name="position">- ������� ���������</param>
	Enemy(std::string name, Model* model, glm::vec3 position, bool has_impulse, bool has_weapon);
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
	void collider_solver(Object* object) override;
};