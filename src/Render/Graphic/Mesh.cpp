#include "Mesh.h"

Mesh::Mesh()
{
	glGenVertexArrays(1, &vao);
	bind();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
}

void Mesh::bind()
{
	glBindVertexArray(vao);
}

void Mesh::load_buffer(int layout, const std::vector<GLfloat>& vertex_buffer_data)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(GLfloat),
        vertex_buffer_data.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(layout);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(
        layout,     // Атрибут. Здесь необязательно указывать 1, но главное, чтобы это значение совпадало с layout в шейдере..
        3,          // Размер
        GL_FLOAT,   // Тип
        GL_FALSE,   // Нормализован?
        0,          // Шаг
        (void*)0);  // Смещение
    buffers.push_back(vbo);
}

void Mesh::depth_mode()
{
    // Включить тест глубины
    glEnable(GL_DEPTH_TEST);
    // Фрагмент будет выводиться только в том, случае, если он находится ближе к камере, чем предыдущий
    glDepthFunc(GL_LESS);
}

void Mesh::cut_mode()
{
    // Отсечение тех треугольников, нормаль которых направлена от камеры
    glEnable(GL_CULL_FACE);
}

void Mesh::draw(int count)
{
	glDrawArrays(GL_TRIANGLES, 0, count);
}
