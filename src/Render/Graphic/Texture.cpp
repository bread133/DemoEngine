#include "Texture.h"

void Texture::load_texture(const std::string& path)
{
	// OpenGL загружает изображение снизу, а нам необходимо загружать текстуру сверху
	stbi_set_flip_vertically_on_load(true);
	// Загрузка
	unsigned char* pixels = stbi_load(std::string(path).c_str(), &width, &heigth, &channels, 0);
	if (!pixels)
	{
		std::cout << "Нек удалось загрузить следующую текстуру: " << path << std::endl;
		return;
	}
	// Освобождение памяти
	stbi_image_free(pixels);
}