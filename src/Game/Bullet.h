#pragma once
#include "src/Render/Graphic/Shader.h"
#include "src/Game/Object.h"

#include <string>

const float sprite_vertices[] = {
    // pos
    0.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f
};

class Bullet : Object
{
	float speed;
	float length;
	bool alive;
	Model* model;
	void get_position();
public:
	Bullet(Model* model, glm::vec3 position, glm::vec3 scale, float speed, float length);
	~Bullet();
	void draw(Shader *shader);
};