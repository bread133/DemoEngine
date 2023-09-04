#include "Object.h"

Object::Object(Model* model, float x_position, float y_position, float z_position) :
	model(model),
	position(glm::vec3(x_position, y_position, z_position)),
	scale(glm::vec3(1.0f, 1.0f, 1.0f))
{
}

Object::Object(Model* model, float x_position, float y_position, float z_position, float x_scale, float y_scale, float z_scale) :
	model(model),
	position(glm::vec3(x_position, y_position, z_position)),
	scale(glm::vec3(x_scale, y_scale, z_scale))
{
}

Object::~Object()
{
	delete model;
}

void Object::draw(Shader* shader)
{
	model->draw(shader);
}
