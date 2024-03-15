#pragma once
#include "Level.h"

class Game
{
	Window* window;
	Shader* object_shader;
	Shader* skybox_shader;
	std::vector<Level*> levels;
	int index;
	bool win = false;
	void next_level();
	void render();
public:
	Game(Window* window, Shader* object_shader,	Shader* skybox_shader);
	~Game();
	void add_level(Level* level);
	void start();
};