#pragma once

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"
#include <iostream>
#include <string>

class Texture
{
	int width;
	int heigth;
	int channels;

	void load_texture(const std::string& path);
};