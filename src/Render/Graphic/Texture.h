#pragma once

#include<glad/glad.h>
#include <iostream>
#include <string>
#include <vector>

class Texture
{
	unsigned int id;
	int width;
	int heigth;
	int channels;
public:
	Texture();
	~Texture();
	void create_texture(const std::string& path);
	void bind();
	void load(int layout, std::vector<float> data);
	// нужно создать функции альясинга и конфигураторы

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
};