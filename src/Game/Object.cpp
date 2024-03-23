#include "Object.h"

Object::Object(Model* model, glm::vec3 position) :
	model(model),
	position(position),
	scale(glm::vec3(1.0f, 1.0f, 1.0f)),
	min_coords(glm::vec3(0.0f)),
	max_coords(glm::vec3(0.0f)),
	velosity(glm::vec3(0.0f))
{
}

Object::Object(Model* model, glm::vec3 position, glm::vec3 scale) :
	model(model),
	position(position),
	scale(scale),
	min_coords(glm::vec3(0.0f)),
	max_coords(glm::vec3(0.0f)),
	velosity(glm::vec3(0.0f))
{
}



Object::~Object()
{
	delete model;
}

void Object::load()
{
	model->load_model();
	// init size or min_max points
	
}

void Object::draw(Shader* shader, Window* window, Camera* camera, float delta_time)
{
	camera->mvp_transformation(window, shader, position, scale);
	model->draw(shader);
}
