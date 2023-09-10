#pragma once
#include "../Render/Graphic/Model.h"
#include "../Render/Graphic/Shader.h"
#include "../Render/Window.h"
#include "../Render/Graphic/Camera.h"

#include <vector>

class Object
{
protected:
	glm::vec3 position;
	glm::vec3 scale;
	Model* model;
public:
	Object(Model* model, glm::vec3 position);
	Object(Model* model, glm::vec3 position, glm::vec3 scale);
	~Object();
	virtual void draw(Shader* shader, Window* window, Camera* camera);
};