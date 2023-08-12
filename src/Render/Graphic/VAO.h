#pragma once
#include <glad/glad.h>
#include <vector>

class VAO
{
	GLuint vao;
	std::vector<GLfloat> buffers;
public:
	VAO();
	~VAO();
	void bind();
	void load_buffer(int layout, const std::vector<GLfloat>& vertex_buffer_data);
	void depth_mode();
	void draw(int count);
	VAO(const VAO& other) = delete;
};