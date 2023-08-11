#include "VAO.h"

#include<GLFW/glfw3.h>
#include<glad/glad.h>

VAO::VAO()
{
	glGenVertexArrays(1, &vao);
	Bind();
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &vao);
}

void VAO::Bind()
{
	glBindVertexArray(vao);
}
