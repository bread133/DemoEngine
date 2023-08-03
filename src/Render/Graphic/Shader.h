#pragma once

#include <string>

class Shader 
{
public:
	unsigned int id;

	Shader() = delete;
	Shader(unsigned int id);
	~Shader();
	void use();
	static int load_shaders(const char* vertex_file_path, const char* fragment_file_path);
};

extern Shader* load(const char* vertex_file_path, const char* fragment_file_path);