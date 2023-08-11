#pragma once
#include <glad/glad.h>

class VAO
{
	GLuint vao;
public:
	VAO();
	~VAO();
	void Bind();
};