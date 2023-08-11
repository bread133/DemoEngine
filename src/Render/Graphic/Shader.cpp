#include "Shader.h"

#include <glad/glad.h>
#include <gl/GL.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

Shader::Shader(unsigned int id) : id(id) {
}

Shader::~Shader() {
	glDeleteProgram(id);
}

void Shader::use() {
	glUseProgram(id);
}

int Shader::load_shaders(const char* vertex_file_path, const char* fragment_file_path) {

	// Создаем шейдеры
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	// Считываем вертексный шейдер из файла, указанного в виде пути в vertex_file_path
	std::string vertex_shader_code;
	std::ifstream vertex_shader_stream(vertex_file_path, std::ios::in);
	if (vertex_shader_stream.is_open()) {
		std::stringstream sstr;
		sstr << vertex_shader_stream.rdbuf();
		vertex_shader_code = sstr.str();
		vertex_shader_stream.close();
	}
	else {
		printf_s("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Считываем фрагментный шейдер из файла, указанного в виде пути в fragment_file_path
	std::string fragment_shader_code;
	std::ifstream fragment_shader_stream(fragment_file_path, std::ios::in);
	if (fragment_shader_stream.is_open()) {
		std::stringstream sstr;
		sstr << fragment_shader_stream.rdbuf();
		fragment_shader_code = sstr.str();
		fragment_shader_stream.close();
	}
	else {
		printf_s("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", fragment_file_path);
		getchar();
		return 0;
	}

	GLint result = GL_FALSE;
	int info;

	// Компиляция вертексного шейдера
	printf_s("Compiling shader : %s\n", vertex_file_path);
	char const* vertex_source_pointer = vertex_shader_code.c_str();
	glShaderSource(vertex_shader_id, 1, &vertex_source_pointer, NULL);
	glCompileShader(vertex_shader_id);

	// Тест-чек вертексного шейдера
	glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info);
	if (info > 0) {
		std::vector<char> VertexShaderErrorMessage(info + 1);
		glGetShaderInfoLog(vertex_shader_id, info, NULL, &VertexShaderErrorMessage[0]);
		printf_s("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Компиляция фрагментного шейдера
	printf_s("Compiling shader : %s\n", fragment_file_path);
	char const* fragment_source_pointer = fragment_shader_code.c_str();
	glShaderSource(fragment_shader_id, 1, &fragment_source_pointer, NULL);
	glCompileShader(fragment_shader_id);

	// Тест-чек фрагментного шейдера
	glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info);
	if (info > 0) {
		std::vector<char> fragment_shader_error_mes(info + 1);
		glGetShaderInfoLog(fragment_shader_id, info, NULL, &fragment_shader_error_mes[0]);
		printf_s("%s\n", &fragment_shader_error_mes[0]);
	}

	// Линковка программы шейдера
	printf_s("Linking program\n");
	GLuint program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);

	// Проверка программы шейдера
	glGetProgramiv(program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info);
	if (info > 0) {
		std::vector<char> program_error_mes(info + 1);
		glGetProgramInfoLog(program_id, info, NULL, &program_error_mes[0]);
		printf_s("%s\n", &program_error_mes[0]);
	}

	// Отключаем шейдеры
	glDetachShader(program_id, vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);

	// Удаляем шейдеры
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	return program_id;
}
// Получить хэндл переменной в шейдере
GLuint Shader::get_uniform_location(glm::mat4 MVP)
{
	GLuint matrix_id = glGetUniformLocation(id, "MVP");
	return matrix_id;
}
// Передать наши трансформации в текущий шейдер
// Это делается в основном цикле, поскольку каждая модель будет иметь другую MVP-матрицу (как минимум часть M)
void Shader::get_uniform_matrix(GLuint matrix_id, glm::mat4 MVP)
{
	glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &MVP[0][0]);
}

Shader* load(const char* vertex_file_path, const char* fragment_file_path)
{
	return new Shader(Shader::load_shaders(vertex_file_path, fragment_file_path));
}
