#pragma once
#include "../Render/Graphic/Model.h"
#include "../Render/Graphic/Shader.h"

class Object
{
protected:
	glm::vec3 position;
	glm::vec3 scale;
	Model* model;
public:
	Object(Model* model, float x_position, float y_position, float z_position);
	Object(Model* model, float x_position, float y_position, float z_position, float x_scale, float y_scale, float z_scale);
	~Object();
	virtual void draw(Shader* shader);
};