#pragma once
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Window.h"

class Camera 
{
	glm::vec3 position;		// позиция
	float horizontal_angle;	// горизонтальный угол
	float vertical_angle;	// вертикальный угол
	float initial_fov;		// поле обзора
	float speed;
	float mouse_speed;

	glm::vec3 get_direction();
	glm::vec3 get_right();
	glm::vec3 get_up();
	void get_mouse_position(Window* window, float delta_time);
public:
	Camera();
	Camera(float initial_fov, float speed, float mouse_speed, float x_pos, float y_pos, float z_pos);
	~Camera();
	glm::mat4 get_MVP();
	void input(Window* window, float delta_time);
};