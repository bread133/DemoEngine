#include "Camera.h"

Camera::Camera()
{
	position = glm::vec3(0, 0, 5);
	horizontal_angle = 3.14f;
	vertical_angle = 0.0f;
	initial_fov = 45.0f;
	speed = 0.003f; // units / second
	mouse_speed = 0.001f;
}

Camera::Camera(float initial_fov, float speed, float mouse_speed, float x_pos, float y_pos, float z_pos) :
	initial_fov(initial_fov),
	speed(speed),
	mouse_speed(mouse_speed)
{
	position = glm::vec3(x_pos, y_pos, z_pos);
	horizontal_angle = 3.14f;
	vertical_angle = 0.0f;
}

Camera::~Camera()
{
}

void Camera::get_mouse_position(Window* window, float delta_time)
{
	int width, heigth;
	glfwGetWindowSize(window->window, &width, &heigth);

	double xpos, ypos;
	glfwGetCursorPos(window->window, &xpos, &ypos);
	// std::cout << xpos << '\t' << ypos << std::endl;
	// �������� ������� ���� ��� ���������� �����
	glfwSetCursorPos(window->window, width / 2, heigth / 2);
	horizontal_angle += mouse_speed * delta_time * float(width / 2 - xpos);
	vertical_angle += mouse_speed * delta_time * float(heigth / 2 - ypos);
	// �������� ��� ����� ������, ��� ��� �������� ���������, � �� ��� ������ ��������!!!!
	if (vertical_angle < -1)
		vertical_angle = -1;
	if (vertical_angle > 1)
		vertical_angle = 1;
}

glm::mat4 Camera::get_MVP()
{
	// ������������ �������: ���� ������ = FoV, ��������� ������ 4 � 3, ��������� ��������� 0.1 � 100 ������
	glm::mat4 projection = glm::perspective(glm::radians(initial_fov), 
		4.0f / 3.0f, 0.1f, 100.0f);
	// ������� ������
	glm::mat4 view = glm::lookAt(
		position,					// ������� ������
		position + get_direction(),	// ����������� ������
		get_up()					// ������ "�����" ������
	);
	glm::mat4 model = glm::mat4(1.0);
	return projection * view * model;
}

glm::vec3 Camera::get_direction()
{
	// �����������
	return glm::vec3(
		cos(vertical_angle) * sin(horizontal_angle),
		sin(vertical_angle),
		cos(vertical_angle) * cos(horizontal_angle)
	);
}

glm::vec3 Camera::get_right()
{
	// ������, ����������� ����������� ������ �� ������
	return glm::vec3(
		sin(horizontal_angle - 3.14f / 2.0f),
		0,
		cos(horizontal_angle - 3.14f / 2.0f)
	);
}

glm::vec3 Camera::get_up()
{
	return glm::vec3(glm::cross(get_right(), get_direction()));
}

void Camera::input(Window* window, float delta_time)
{
	// �������� ������
	if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS ||
		glfwGetKey(window->window, GLFW_KEY_UP) == GLFW_PRESS) {
		position += get_direction() * delta_time * speed;
		position.y = 0;
	}
	// �������� �����
	if (glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS ||
		glfwGetKey(window->window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		position -= get_direction() * delta_time * speed;
		position.y = 0;
	}
	// ������ ������
	if (glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS ||
		glfwGetKey(window->window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position += get_right() * delta_time * speed;
		position.y = 0;
	}
	// ������ �����
	if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS ||
		glfwGetKey(window->window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		position -= get_right() * delta_time * speed;
		position.y = 0;
	}
	
	get_mouse_position(window, delta_time);
}

