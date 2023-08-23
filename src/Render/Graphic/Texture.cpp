#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

Texture::Texture()
{
	glGenTextures(1, &id);
	bind();
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::create_texture(const std::string& path)
{
	// OpenGL загружает изображение снизу, а нам необходимо загружать текстуру сверху
	stbi_set_flip_vertically_on_load(true);
	// Загрузка
	unsigned char* pixels = stbi_load(std::string(path).c_str(), &width, &heigth, &channels, 0);
	if (!pixels)
	{
		std::cout << "Не удалось загрузить следующую текстуру: " << path << std::endl;
		return;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, heigth, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Освобождение памяти
	stbi_image_free(pixels);
}

void Texture::bind() 
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::load(int layout, std::vector<float> data)
{
	glVertexAttribPointer(
		layout,
		2,
		GL_FLOAT, 
		GL_FALSE, 
		0,
		(void*)0);
	glEnableVertexAttribArray(layout);
}