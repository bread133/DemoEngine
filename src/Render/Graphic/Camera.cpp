#include "Camera.h"

// constructor with vectors
Camera::Camera(glm::vec3 position) : 
    direction(glm::vec3(0.0f, 0.0f, -1.0f)), 
    speed(SPEED), 
    mouse_speed(SENSITIVITY), 
    zoom(ZOOM),
    initial_fov(FOV)
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    horizontal_angle = HORIZONTAL_ANGLE;
    vertical_angle = VERTICAL_ANGLE;
    updateCameraVectors();
}
// constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float fov) :
    direction(glm::vec3(0.0f, 0.0f, -1.0f)),
    speed(SPEED),
    mouse_speed(SENSITIVITY),
    zoom(ZOOM),
    initial_fov(fov)
{
    position = glm::vec3(posX, posY, posZ);
    world_up = glm::vec3(upX, upY, upZ);
    horizontal_angle = yaw;
    vertical_angle = pitch;
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::get_view_matrix()
{
    return glm::lookAt(position, position + direction, up);
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
    case 4:
        position += world_up * speed * delta_time;
        break;
    case 5:
        position -= world_up * speed * delta_time;
        break;
    }
}

// calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    direction = glm::vec3(
        cos(vertical_angle) * sin(horizontal_angle),
        sin(vertical_angle),
        cos(vertical_angle) * cos(horizontal_angle)
    );
    // also re-calculate the Right and Up vector
    right = glm::vec3(
        sin(horizontal_angle - 3.14f / 2.0f),
        0,
        cos(horizontal_angle - 3.14f / 2.0f)
    );
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, direction));
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

    updateCameraVectors();
}

void Camera::mvp_transformation(int WIDTH, int HEIGHT, Shader* shader)
{
    glm::mat4 projection = glm::perspective(glm::radians(initial_fov),
        4.0f / 3.0f, 0.1f, 100.0f);
   
    glm::mat4 view = glm::lookAt(
        position,					
        position + direction,	
        up					
    );
    
    shader->set_mat4("projection", projection);
    shader->set_mat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    shader->set_mat4("model", model);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
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