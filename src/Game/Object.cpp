#include "Object.h"

Object::Object(Model* model, glm::vec3 position) :
	model(model),
	position(position),
	scale(glm::vec3(1.0f, 1.0f, 1.0f))
{
}

Object::Object(Model* model, glm::vec3 position, glm::vec3 scale) :
	model(model),
	position(position),
	scale(scale)
{
}



Object::~Object()
{
	delete model;
}

void Object::load()
{
	model->load_model();
}

void Object::draw(Shader* shader, Window* window, Camera* camera, float delta_time)
{
	camera->mvp_transformation(window, shader, position, scale);
	model->draw(shader);
}
