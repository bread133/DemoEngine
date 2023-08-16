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
        layout,     // �������. ����� ������������� ��������� 1, �� �������, ����� ��� �������� ��������� � layout � �������..
        3,          // ������
        GL_FLOAT,   // ���
        GL_FALSE,   // ������������?
        0,          // ���
        (void*)0);  // ��������
    buffers.push_back(vbo);
}

void Mesh::depth_mode()
{
    // �������� ���� �������
    glEnable(GL_DEPTH_TEST);
    // �������� ����� ���������� ������ � ���, ������, ���� �� ��������� ����� � ������, ��� ����������
    glDepthFunc(GL_LESS);
}

void Mesh::cut_mode()
{
    // ��������� ��� �������������, ������� ������� ���������� �� ������
    glEnable(GL_CULL_FACE);
}

void Mesh::draw(int count)
{
	glDrawArrays(GL_TRIANGLES, 0, count);
}
