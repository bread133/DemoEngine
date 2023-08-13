#include "Camera.h"

glm::vec3 position = glm::vec3(0, 0, 5);
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;

Camera::Camera()
{
	float initialFoV = 45.0f;
	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;
}

void Camera::get_mouse_position()
{
	double xpos, ypos;
	glfwGetCursorPos(Window::window, &xpos, &ypos);
	std::cout << xpos << '\t' << ypos << std::endl;
}

