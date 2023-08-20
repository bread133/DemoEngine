#include "Texture.h"

void Texture::load_texture(const std::string& path)
{
	// OpenGL ��������� ����������� �����, � ��� ���������� ��������� �������� ������
	stbi_set_flip_vertically_on_load(true);
	// ��������
	unsigned char* pixels = stbi_load(std::string(path).c_str(), &width, &heigth, &channels, 0);
	if (!pixels)
	{
		std::cout << "��� ������� ��������� ��������� ��������: " << path << std::endl;
		return;
	}
	// ������������ ������
	stbi_image_free(pixels);
}