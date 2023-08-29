#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    void load(const char* vertexPath, const char* fragmentPath);
    void checkCompileErrors(GLuint shader, std::string type);
public:
    unsigned int id;

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void use();
    void set_mat4(const std::string& name, const glm::mat4& mat) const;
};
#endif