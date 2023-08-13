#pragma once
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <vector>

class Mesh
{
	GLuint vao;
	std::vector<GLfloat> buffers;
public:
	Mesh();
	~Mesh();
	void bind();
	void load_buffer(int layout, const std::vector<GLfloat>& vertex_buffer_data);
	void depth_mode();
	void draw(int count);
	Mesh(const Mesh& other) = delete;
};