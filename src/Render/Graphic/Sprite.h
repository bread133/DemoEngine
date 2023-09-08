#pragma once
#include "Shader.h"
#include "Model.h"

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

class Sprite
{
	float position;
	float speed;
	float scale;
	float length;
	unsigned int texture;
	void get_position();
	void load(std::string path);
public:
	Sprite(float position, float speed, float scale, float length, std::string path);
	~Sprite();
	void draw(Shader *shader);
};