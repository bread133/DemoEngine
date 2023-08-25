#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Model 
{
	std::vector<Vertex> vertex;
public:
	Model();
	~Model();
	void load(const char* filename);

};