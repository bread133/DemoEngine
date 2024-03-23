#pragma once
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"

#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <string>

class Mesh 
{
    unsigned int VBO, EBO;
    void setup_mesh();
public:
    // данные о мешах
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
    unsigned int VAO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    ~Mesh();
    // отрисовка всех мешей
    void draw(Shader*& shader);
};