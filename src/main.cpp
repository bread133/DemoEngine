#include "Render/Window.h"
#include "Render/Graphic/Shader.h"
#include "Render/Graphic/VAO.h"

#include <iostream>
#include <glad/glad.h>
#include <gl/GL.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Window dimensions
const int WIDTH = 1080, HEIGHT = 720;

// вершины фигуры
static const GLfloat g_vertex_buffer_data[] = {
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
};

// цвет
static const GLfloat g_color_buffer_data[] = {
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
};

int main()
{
    // Проекционная матрица : 45&deg; поле обзора, 4:3 соотношение сторон, диапазон : 0.1 юнит <-> 100 юнитов
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Или, для ортокамеры
    glm::mat4 View = glm::lookAt(
        glm::vec3(4, 0, -3), // Камера находится в мировых координатах (4,3,3)
        glm::vec3(0, 0, 0), // И направлена в начало координат
        glm::vec3(0, 1, 0)  // "Голова" находится сверху
    );

    // Матрица модели : единичная матрица (Модель находится в начале координат)
    glm::mat4 Model = glm::mat4(1.0f);  // Индивидуально для каждой модели
    // Итоговая матрица ModelViewProjection, которая является результатом перемножения наших трех матриц
    glm::mat4 MVP = Projection * View * Model; // Помните, что умножение матрицы производиться в обратном порядке

    Window::initialize(WIDTH, HEIGHT, "Demo");
    Window::colored(0.1f, 0.0f, 1.0f, 0.7f);

    GLuint VBO, CLR;
    VAO* vao = new VAO();

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), 
        g_vertex_buffer_data, GL_STATIC_DRAW);

    // цвет
    glGenBuffers(1, &CLR);
    glBindBuffer(GL_ARRAY_BUFFER, CLR);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), 
        g_color_buffer_data, GL_STATIC_DRAW);
    
    Shader* shader = load("C://Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Templates/triangle.glslv", 
        "C://Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Templates/triangle.glslf");

    // вершины
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // цвет
    // Второй буфер атрибутов - цвета
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, CLR);
    glVertexAttribPointer(
        1,                                // Атрибут. Здесь необязательно указывать 1, но главное, чтобы это значение совпадало с layout в шейдере..
        3,                                // Размер
        GL_FLOAT,                         // Тип
        GL_FALSE,                         // Нормализован?
        0,                                // Шаг
        (void*)0                          // Смещение
    );

    GLuint matrix_id = shader->get_uniform_location(MVP);

    // Включить тест глубины
    glEnable(GL_DEPTH_TEST);
    // Фрагмент будет выводиться только в том, случае, если он находится ближе к камере, чем предыдущий
    glDepthFunc(GL_LESS);

    // Игровой цикл
    while (!Window::window_is_closed())
    {
        Window::clear();

        shader->get_uniform_matrix(matrix_id, MVP);
        shader->use();

        vao->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

        Window::swap_buffers();
        Window::poll_events();
    }

    glDeleteBuffers(1, &VBO);
    delete vao;
    delete shader;
    Window::terminate();
    return 0;
}