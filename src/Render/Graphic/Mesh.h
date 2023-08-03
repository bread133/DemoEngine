#pragma once

class GLfloat;
class GLuint;

class Mesh 
{
	GLuint VAO;
	GLuint VBO;
public:
	Mesh();
	void generate();
	void bind(static const GLfloat* vertex_buffer_data);
	void activate();
	void draw();
	void discard();
};