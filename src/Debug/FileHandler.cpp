#include "FileHandler.h"

void FileHandler::write_line(std::string path, std::string text)
{
	std::ofstream f;
	f.open(path, std::ios::app);

	f << "[" << std::chrono::system_clock::now() << "]: " << text << std::endl;
	f.close();
}

void FileHandler::write_line(std::string path, const char* text)
{
	std::ofstream f;
	f.open(path, std::ios::app);

	f << "[" << std::chrono::system_clock::now() << "]: " << text << std::endl;
	f.close();
}

void FileHandler::write_line_load_object(std::string name)
{
	std::string path = "C:/Users/bread/source/repos/DemoEngineWithCMake/src/Debug/logs.txt";
	std::string str = "load object " + name;
	FileHandler::write_line(path, str);
}

void FileHandler::write_line_collider_parameters(Collider* collider)
{
	std::string path = "C:/Users/bread/source/repos/DemoEngineWithCMake/src/Debug/logs.txt";
	std::string str = "\ncollider: " + std::to_string(collider->collider_type);
	str += "\ncenter: " + get_vector_string(collider->center);
	switch(collider->collider_type)
	{
	case SPHERE:
		str += "\nradius: ";
		str += get_vector_string(collider->collision_points.max_point);
		break;
	case PARALLELEPIPED:
		str += "\nmax_point: " + get_vector_string(collider->collision_points.max_point);
		str += "\nmin_point: " + get_vector_string(collider->collision_points.min_point);
		break;
	case NONE:
		break;
	default:
		throw("Что-то пошло не так...");
	}
	FileHandler::write_line(path, str);
}

void FileHandler::write_line_position(glm::vec3 vec, std::string name)
{
	std::string path = "C:/Users/bread/source/repos/DemoEngineWithCMake/src/Debug/logs.txt";
	std::string str = "position of object: " + name
		+ get_vector_string(vec);
	FileHandler::write_line(path, str);
}

std::string FileHandler::get_vector_string(glm::vec3 vec)
{
	return  "(" + std::to_string(vec.x) + "; " + std::to_string(vec.y) + 
		"; " + std::to_string(vec.z) + ")";
}
