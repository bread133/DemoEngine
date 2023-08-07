#pragma once
#include <glad/glad.h>

class Mesh 
{
	
public:
	GLuint VAO;
	GLuint VBO;

	Mesh();
	void generate();
	void bind(static const GLfloat* vertex_buffer_data);
	void activate();
	void draw();
	void discard();
};