#pragma once

#include <string>
#include <glm/mat4x4.hpp>
#include<glad/glad.h>

class Shader 
{
public:
	unsigned int id;

	Shader() = delete;
	Shader(unsigned int id);
	~Shader();
	void use();
	static int load_shaders(const char* vertex_file_path, const char* fragment_file_path);
	GLuint get_uniform_location(glm::mat4 MVP);
	void get_uniform_matrix(GLuint matrix_id, glm::mat4 MVP);
};

extern Shader* load(const char* vertex_file_path, const char* fragment_file_path);