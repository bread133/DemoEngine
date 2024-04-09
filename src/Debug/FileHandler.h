#pragma once

#include <iostream>
#include <fstream>
#include <chrono>

#include "src/Physic/Collider.h"
#include "src/Game/Object.h"

struct FileHandler 
{
	static void write_line(std::string path, std::string text);
	static void write_line(std::string path, const char* text);
	static void write_line_load_object(std::string name);
	static void write_line_collider_parameters(Collider* collider);
	static void write_line_position(glm::vec3 vec, std::string name);

	static std::string get_vector_string(glm::vec3 vec);
};