#include "Render/Window.h"
#include "Render/Graphic/Shader.h"
#include "Render/Graphic/Mesh.h"
#include "Render/Graphic/Camera.h"

#include <iostream>
#include <glad/glad.h>
#include <gl/GL.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Window dimensions
const int WIDTH = 1080, HEIGHT = 720;

int main()
{
    // Проекционная матрица : 45&deg; поле обзора, 4:3 соотношение сторон, диапазон : 0.1 юнит <-> 100 юнитов
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Или, для ортокамеры
    glm::mat4 view = glm::lookAt(
        glm::vec3(4, 3, 3), // Камера находится в мировых координатах (4,3,3)
        glm::vec3(0, 0, 0), // И направлена в начало координат
        glm::vec3(0, 1, 0)  // "Голова" находится сверху
    );
    // Матрица модели : единичная матрица (Модель находится в начале координат)
    glm::mat4 model = glm::mat4(1.0f);  // Индивидуально для каждой модели
    // Итоговая матрица ModelViewProjection, которая является результатом перемножения наших трех матриц
    glm::mat4 MVP = projection * view * model; // Помните, что умножение матрицы производиться в обратном порядке

    Window* window = new Window();
    window->initialize(WIDTH, HEIGHT, "Demo");
    window->colored(0.1f, 0.0f, 1.0f, 0.7f);

    Mesh* mesh = new Mesh();
    mesh->load_buffer(0, 
        {
            -1.0f,-1.0f,-1.0f, // Треугольник 1 : начало
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // Треугольник 1 : конец
            1.0f, 1.0f,-1.0f, // Треугольник 2 : начало
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f, // Треугольник 2 : конец
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
        });

    mesh->load_buffer(1, 
        {
            0.583f,  0.771f,  0.014f,
            0.609f,  0.115f,  0.436f,
            0.327f,  0.483f,  0.844f,
            0.822f,  0.569f,  0.201f,
            0.435f,  0.602f,  0.223f,
            0.310f,  0.747f,  0.185f,
            0.597f,  0.770f,  0.761f,
            0.559f,  0.436f,  0.730f,
            0.359f,  0.583f,  0.152f,
            0.483f,  0.596f,  0.789f,
            0.559f,  0.861f,  0.639f,
            0.195f,  0.548f,  0.859f,
            0.014f,  0.184f,  0.576f,
            0.771f,  0.328f,  0.970f,
            0.406f,  0.615f,  0.116f,
            0.676f,  0.977f,  0.133f,
            0.971f,  0.572f,  0.833f,
            0.140f,  0.616f,  0.489f,
            0.997f,  0.513f,  0.064f,
            0.945f,  0.719f,  0.592f,
            0.543f,  0.021f,  0.978f,
            0.279f,  0.317f,  0.505f,
            0.167f,  0.620f,  0.077f,
            0.347f,  0.857f,  0.137f,
            0.055f,  0.953f,  0.042f,
            0.714f,  0.505f,  0.345f,
            0.783f,  0.290f,  0.734f,
            0.722f,  0.645f,  0.174f,
            0.302f,  0.455f,  0.848f,
            0.225f,  0.587f,  0.040f,
            0.517f,  0.713f,  0.338f,
            0.053f,  0.959f,  0.120f,
            0.393f,  0.621f,  0.362f,
            0.673f,  0.211f,  0.457f,
            0.820f,  0.883f,  0.371f,
            0.982f,  0.099f,  0.879f
        });
    
    Shader* shader = load("C://Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Templates/Shaders/cube.glslv", 
        "C://Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Templates/Shaders/cube.glslf");

    GLuint matrix_id = shader->get_uniform_location(MVP);
    mesh->depth_mode();
    mesh->cut_mode();

    Camera* camera = new Camera();

    // Игровой цикл
    float last_delta_time = 0;
    while (!window->window_is_closed())
    {
        window->clear();

        shader->get_uniform_matrix(matrix_id, MVP);
        shader->use();

        mesh->bind();
        mesh->draw(12 * 3);

        window->swap_buffers();
        window->poll_events();

        float delta_time = Window::get_delta_time(last_delta_time);
        camera->input(window, delta_time);

        // Выход из программы, оформить в класс window, но как сделать break?
        // Хотя эта кнопка нужна будет для вызова меню, если я сделаю
        if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            std::cout << "ESC is pressed" << std::endl;
            break;
        }

        MVP = camera->get_MVP();
    }

    delete camera;
    delete mesh;
    delete shader;
    window->terminate();
    delete window;

    return 0;
}