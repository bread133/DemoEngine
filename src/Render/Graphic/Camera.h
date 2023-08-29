#pragma once
#include "Shader.h"
#include "../Window.h"
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Default camera values
const float HORIZONTAL_ANGLE = 3.14f;
const float VERTICAL_ANGLE = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.5f;
const float ZOOM = 45.0f;
const float FOV = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
    // camera Attributes
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;
    // euler Angles
    float horizontal_angle;
    float vertical_angle;
    // camera options
    float initial_fov;
    float speed;
    float mouse_speed;
    float zoom;

    void update_camera_vectors();
    void get_mouse_position(Window* window, float delta_time);
    glm::mat4 get_view_matrix();
    void process_keyboard(Camera_Movement direction, float deltaTime);
public:
    // constructor with vectors
    Camera(glm::vec3 position);
    // constructor with scalar values
    Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch, float fov);
    ~Camera();
    void input(Window* window, float delta_time);
    void mvp_transformation(int WIDTH, int HEIGHT, Shader* shader);
};