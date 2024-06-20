#pragma once
#include <src/Game/Level.h>
#include <src/Game/Player.h>

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
	bool has_impulse_for_bullet;
public:
	Game(Window* window, Shader* object_shader,	Shader* skybox_shader, bool has_impulse_for_bullet);
	~Game();
	void add_level(Level* level);
	void start();
};