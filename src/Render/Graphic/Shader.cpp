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

	// ������� �������
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// ��������� ���������� ������ �� �����, ���������� � ���� ���� � vertex_file_path
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf_s("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// ��������� ����������� ������ �� �����, ���������� � ���� ���� � fragment_file_path
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}
	else {
		printf_s("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", fragment_file_path);
		getchar();
		return 0;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// ���������� ����������� �������
	printf_s("Compiling shader : %s\n", vertex_file_path);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// ����-��� ����������� �������
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf_s("%s\n", &VertexShaderErrorMessage[0]);
	}

	// ���������� ������������ �������
	printf_s("Compiling shader : %s\n", fragment_file_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// ����-��� ������������ �������
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf_s("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// �������� ��������� �������
	printf_s("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// �������� ��������� �������
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf_s("%s\n", &ProgramErrorMessage[0]);
	}

	// ��������� �������
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	// ������� �������
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
// �������� ����� ���������� � �������
GLuint Shader::get_uniform_location(glm::mat4 MVP)
{
	GLuint matrix_id = glGetUniformLocation(id, "MVP");
	return matrix_id;
}
// �������� ���� ������������� � ������� ������
// ��� �������� � �������� �����, ��������� ������ ������ ����� ����� ������ MVP-������� (��� ������� ����� M)
void Shader::get_uniform_matrix(GLuint matrix_id, glm::mat4 MVP)
{
	glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &MVP[0][0]);
}

Shader* load(const char* vertex_file_path, const char* fragment_file_path)
{
	return new Shader(Shader::load_shaders(vertex_file_path, fragment_file_path));
}
