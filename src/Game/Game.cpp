#include "Game.h"

Game::Game(Window* window, Shader* object_shader, Shader* skybox_shader) :
	window(window),
	object_shader(object_shader),
	skybox_shader(skybox_shader)
{
	index = 0;

	object_shader->use();

	skybox_shader->use();
	skybox_shader->set_int("skybox", 0);
}

Game::~Game()
{
	window->terminate();
	delete skybox_shader;
	delete object_shader;
	delete window;
}

void Game::add_level(Level* level)
{
	levels.push_back(level);
}

void Game::next_level()
{
	if (levels[index]->get_status())
		index++;
	// тут должен быть unload предыдущего уровня
	if (index == levels.size()) 
	{
		win = true;
		std::cout << "You are winner!" << std::endl;
		return;
	}
}

void Game::render()
{
	// цикл уровня с номером index
	while (!levels[index]->get_status())
	{
		levels[index]->draw(window, object_shader, skybox_shader);
		if (window->is_exit())
			break;
	}
}

void Game::start()
{
	// всякие проверки
	if (levels.empty())
		throw;

	while(!window->window_is_closed() && !win)
	{
		// тут должен быть init текущего уровня
		levels[index]->load();
		levels[index]->load_bullet();

		render();
		if (window->is_exit())
			break;
		next_level();
	}
}
