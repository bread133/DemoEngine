#include "Render/Window.h"
#include "Render/Graphic/Shader.h"

#include <iostream>
#include <glad/glad.h>
#include <gl/GL.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Window dimensions
const int WIDTH = 1080, HEIGHT = 720;

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // ����������� 1 : ������
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // ����������� 1 : �����
    1.0f, 1.0f,-1.0f, // ����������� 2 : ������
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // ����������� 2 : �����
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

int main()
{
    // ������������ ������� : 45&deg; ���� ������, 4:3 ����������� ������, �������� : 0.1 ���� <-> 100 ������
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // ���, ��� ����������
    glm::mat4 View = glm::lookAt(
        glm::vec3(4, 3, 3), // ������ ��������� � ������� ����������� (4,3,3)
        glm::vec3(0, 0, 0), // � ���������� � ������ ���������
        glm::vec3(0, 1, 0)  // "������" ��������� ������
    );

    // ������� ������ : ��������� ������� (������ ��������� � ������ ���������)
    glm::mat4 Model = glm::mat4(1.0f);  // ������������� ��� ������ ������
    // �������� ������� ModelViewProjection, ������� �������� ����������� ������������ ����� ���� ������
    glm::mat4 MVP = Projection * View * Model; // �������, ��� ��������� ������� ������������� � �������� �������

    Window::initialize(WIDTH, HEIGHT, "Demo");
    Window::colored(0.5f, 0.0f, 1.0f, 1.0f);

    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), 
        g_vertex_buffer_data, GL_STATIC_DRAW);
    
    Shader* shader = load("C://Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Templates/triangle.glslv", 
        "C://Users/bread/source/repos/DemoEngineWithCMake/DemoEngine/src/Render/Templates/triangle.glslf");

    GLuint matrix_id = shader->get_uniform_location(MVP);
    // Game loop
    while (!Window::window_is_closed())
    {
        Window::poll_events();
        Window::clear();

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        shader->get_uniform_matrix(matrix_id, MVP);
        shader->use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
        glBindVertexArray(0);

        Window::swap_buffers();
    }

    delete shader;
    Window::terminate();
    return 0;
}