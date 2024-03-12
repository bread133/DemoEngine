#pragma once
#include "src/Render/Graphic/Shader.h"
#include "src/Game/Object.h"

#include <string>

/// <summary>
/// ����� ���������
/// </summary>
class Bullet : public Object
{
	glm::vec3 start_position;
	/// <summary>
	/// �������� ��������.
	/// </summary>
	float speed;
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
	Bullet(Model* model, glm::vec3 position, glm::vec3 scale, float speed, float length);
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
	void draw(Shader* shader, Window* window, Camera* camera, float delta_time);
};