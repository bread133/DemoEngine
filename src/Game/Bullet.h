#pragma once
#include "src/Render/Graphic/Shader.h"
#include "src/Game/Object.h"

#include <string>

/// <summary>
/// ����� ���������
/// </summary>
class Bullet final : public Object
{
	glm::vec3 start_position;
	/// <summary>
	/// ����� ��������.
	/// </summary>
	float length;
	/// <summary>
	/// ����������� ��������.
	/// </summary>
	bool is_living;
	void set_position(Camera* camera, float delta_time);
public:
	/// <summary>
	/// �����������.
	/// </summary>
	/// <param name="model">- �������� ���������</param>
	/// <param name="position">- ������� ���������</param>
	/// <param name="scale">- ������ ���������</param>
	/// <param name="speed">- �������� �����</param>
	/// <param name="length">- ����� ��������</param>
	Bullet(std::string name, Model* model, glm::vec3 position, glm::vec3 scale, float speed, float length);
	Bullet(Bullet* bullet);
	/// <summary>
	/// ����������.
	/// </summary>
	~Bullet();
	/// <summary>
	/// 
	/// </summary>
	/// <returns>���� ������� ����� ������� � ������� ������ ������, 
	/// �� false</returns>
	bool get_is_living();
	void set_start_position(Camera* camera);
	void load();
	void draw(Shader* shader, Window* window, Camera* camera, float delta_time);
};