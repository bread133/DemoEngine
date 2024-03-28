#pragma once
#include "../Render/Graphic/Skybox.h"
#include "Enemy.h"
#include "Bullet.h"

#include <vector>
#include <thread>
#include <src/Physic/Map.h>

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
	Bullet* bullet;
	SphereCollider bullet_collider;
	Map* map;
	Skybox* skybox;
	glm::vec3 size;
	bool is_win = false;

	float delta_time = 0.0f;
	float last_frame = 0.0f;
	void add_bullet(Window* window);
	void set_status(Window* window);
public:
	Level(std::string name, Skybox* skybox, glm::vec3 position, bool is_fly);
	Level(std::string name, Skybox* skybox, Camera* camera);
	~Level();

	void win();
	void load();
	void load_bullet();
	void draw(Window* window, Shader* object_shader, Shader* skybox_shader);
	void add_enemy(Enemy* enemy);
	void add_static_object(Object* object);
	bool get_status();
};