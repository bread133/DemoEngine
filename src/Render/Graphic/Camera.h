#pragma once
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include "../Window.h"

class Camera 
{
	glm::vec3 position;		// позиция
	float horizontal_angle;	// горизонтальный угол
	float vertical_angle;	// вертикальный угол
	float initial_fov;		// поле обзора
	float speed;
	float mouse_speed;
	glm::mat4 MVP;
public:
	Camera();
	~Camera();
	static void get_mouse_position();
	glm::mat4 get_MVP();
	void compute_angles();
	glm::vec3 get_direction();
	void input();
};