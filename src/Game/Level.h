#pragma once

#include <src/Render/Graphic/Skybox.h>
#include <src/Render/Graphic/Light.h>

#include <src/Game/Enemy.h>
#include <src/Game/Bullet.h>

#include <src/Physic/Map.h>

#include <vector>
#include <thread>

/// <summary>
///  ласс, позвол€ющий добавить уровень в игру. 
/// ѕредставл€ет из себ€ своеобразную обертку, пр€чет от пользовател€ генерацию шейдеров и прочее.
/// —оздаетс€ новый экземпл€р класса, который работает внутри главного цикла в main.
/// ѕотом будет хранитьс€ в классе Game.
/// </summary>
class Level
{
	Camera* camera;
	std::string name;
	Player* player;
	Map* map;
	Skybox* skybox;
	glm::vec3 size;
	bool is_win = false;

	float delta_time = 0.0f;
	float last_frame = 0.0f;
	void set_status(Window* window);
public:
	Level(std::string name, Skybox* skybox, glm::vec3 position, bool is_fly, Player* player);
	Level(std::string name, Skybox* skybox, Camera* camera, Player* player);
	~Level();

	void win();
	void load();
	void load_bullet(bool has_impulse);
	void draw(Window* window, Shader* object_shader, Shader* skybox_shader);
	void add_enemy(Enemy* enemy);
	void add_static_object(Object* object);
	void add_light(LightPoint* light);
	void remove_light(LightPoint* light);

	bool get_status();
};