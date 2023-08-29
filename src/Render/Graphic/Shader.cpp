#include "Shader.h"

#include <glad/glad.h>
#include <gl/GL.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	load(vertexPath, fragmentPath);
}

Shader::~Shader() {
	glDeleteProgram(id);
}

void Shader::use()
{
	glUseProgram(id);
}

// утилиты для загрузки в файл шейдера
void Shader::set_mat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


void Shader::load(const char* vertexPath, const char* fragmentPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertex_code;
	std::string fragment_code;
	std::string geometry_code;
	std::ifstream vertex_shader_file;
	std::ifstream fragment_shader_file;
	std::ifstream gShaderFile;
	// ensure ifstream objects can throw exceptions:
	vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vertex_shader_file.open(vertexPath);
		fragment_shader_file.open(fragmentPath);
		std::stringstream vertex_shader_stream, fragment_shader_stream;
		// read file's buffer contents into streams
		vertex_shader_stream << vertex_shader_file.rdbuf();
		fragment_shader_stream << fragment_shader_file.rdbuf();
		// close file handlers
		vertex_shader_file.close();
		fragment_shader_file.close();
		// convert stream into string
		vertex_code = vertex_shader_stream.str();
		fragment_code = fragment_shader_stream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::ФАЙЛ НЕ СЧИТЫВАЕТСЯ: " << e.what() << std::endl;
	}
	const char* vertex_shader_code = vertex_code.c_str();
	const char* fragment_shader_code = fragment_code.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertex_shader_code, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragment_shader_code, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	// shader Program
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);
	checkCompileErrors(id, "PROGRAM");

	glDetachShader(id, fragment);
	glDetachShader(id, vertex);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar info_log[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, info_log);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << info_log << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, info_log);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << info_log << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}