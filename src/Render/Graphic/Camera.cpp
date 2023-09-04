#include "Camera.h"

// constructor with vectors
Camera::Camera(glm::vec3 position, bool is_fly) :
    position(glm::vec3(0.0f, 0.0f, 0.0f)),
    world_up(glm::vec3(0.0f, 1.0f, 0.0f)),
    speed(SPEED),
    horizontal_angle(HORIZONTAL_ANGLE),
    vertical_angle(VERTICAL_ANGLE),
    mouse_speed(SENSITIVITY), 
    initial_fov(FOV),
    is_fly(is_fly)
{
    update_camera_vectors();
}
// constructor with scalar values
Camera::Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch, float fov, bool is_fly) :
    position(glm::vec3(pos_x, pos_y, pos_z)),
    world_up(glm::vec3(up_x, up_y, up_z)),
    speed(SPEED),
    horizontal_angle(yaw),
    vertical_angle(pitch),
    mouse_speed(SENSITIVITY),
    initial_fov(fov),
    is_fly(is_fly)
{
    update_camera_vectors();
}

Camera::~Camera()
{
}

glm::vec3 Camera::get_position()
{
    return position;
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::process_keyboard(Camera_Movement move, float delta_time)
{
    switch (move) 
    {
    case 0:
        position += direction * speed * delta_time;
        break;
    case 1:
        position -= direction * speed * delta_time;
        break;
    case 2:
        position -= right * speed * delta_time;
        break;
    case 3:
        position += right * speed * delta_time;
        break;
    }
    if (is_fly)
        process_keyboard_fly(move, delta_time);
}


void Camera::process_keyboard_fly(Camera_Movement move, float delta_time)
{
    switch (move)
    {
    case 4:
        position += world_up * speed * delta_time;
        break;
    case 5:
        position -= world_up * speed * delta_time;
        break;
    }
}


glm::vec3 Camera::get_direction() 
{
    return glm::vec3(
        cos(vertical_angle) * sin(horizontal_angle),
        sin(vertical_angle),
        cos(vertical_angle) * cos(horizontal_angle)
    );
}

glm::vec3 Camera::get_right()
{
    return glm::vec3(
        sin(horizontal_angle - 3.14f / 2.0f),
        0,
        cos(horizontal_angle - 3.14f / 2.0f)
    );
}

void Camera::update_camera_vectors()
{
    direction = get_direction();
    right = get_right();

    up = glm::cross(right, direction);
}

void Camera::get_mouse_position(Window* window, float delta_time)
{
    int width, heigth;
    glfwGetWindowSize(window->window, &width, &heigth);

    double xpos, ypos;
    glfwGetCursorPos(window->window, &xpos, &ypos);
    
    glfwSetCursorPos(window->window, width / 2, heigth / 2);
    horizontal_angle += mouse_speed * delta_time * float(width / 2 - xpos);
    vertical_angle += mouse_speed * delta_time * float(heigth / 2 - ypos);

    if (vertical_angle > 1)
        vertical_angle = 1;
    if (vertical_angle < -1)
        vertical_angle = -1;
    update_camera_vectors();
}

glm::mat4 Camera::get_projection_matrix(int WIDTH, int HEIGHT) 
{
    return glm::perspective(glm::radians(initial_fov),
        (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
}

glm::mat4 Camera::get_view_matrix()
{
    return glm::lookAt(
        position,
        position + direction,
        up
    );
}

void Camera::mvp_transformation(int WIDTH, int HEIGHT, Shader* shader, glm::vec3 translation)
{
    glm::mat4 projection = get_projection_matrix(WIDTH, HEIGHT);
   
    glm::mat4 view = get_view_matrix();
    
    shader->set_mat4("projection", projection);
    shader->set_mat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, translation); // translate it down so it's at the center of the scene
    //model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    shader->set_mat4("model", model);
}

void Camera::input(Window* window, float delta_time)
{
    if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS ||
        glfwGetKey(window->window, GLFW_KEY_UP) == GLFW_PRESS)
        process_keyboard(FORWARD, delta_time);

    if (glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS ||
        glfwGetKey(window->window, GLFW_KEY_DOWN) == GLFW_PRESS)
        process_keyboard(BACKWARD, delta_time);

    if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS ||
        glfwGetKey(window->window, GLFW_KEY_LEFT) == GLFW_PRESS)
        process_keyboard(LEFT, delta_time);

    if (glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS ||
        glfwGetKey(window->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        process_keyboard(RIGHT, delta_time);

    if (glfwGetKey(window->window, GLFW_KEY_TAB) == GLFW_PRESS)
        process_keyboard(UP, delta_time);

    if (glfwGetKey(window->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        process_keyboard(DOWN, delta_time);

    get_mouse_position(window, delta_time);
}