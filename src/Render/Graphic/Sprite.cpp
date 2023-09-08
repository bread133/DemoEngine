#include "Sprite.h"

Sprite::Sprite(float position, float speed, float scale, float length, std::string path) :
	position(position),
	speed(speed),
	length(length),
	scale(scale)
{
	load(path);
}

Sprite::~Sprite()
{

}

void Sprite::draw(Shader* shader)
{

}

void Sprite::load(std::string path)
{
	std::string directory = path.substr(0, path.find_last_of('/'));
	texture = texture_from_file(path.c_str(), directory, false);
}

