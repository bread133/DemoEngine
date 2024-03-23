#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>

/// <summary>
/// Класс окна программы.
/// Обязателен к инициализации.
/// Инициализировать первым делом.
/// </summary>
class Window
{
	/// <summary>
	/// инициализация окна именно в этом методе.
	/// </summary>
	/// <param name="width">- ширина окна</param>
	/// <param name="height">- длина окна</param>
	/// <param name="title">- название игры (тайтл)</param>
	/// <returns>в случае ошибки возвращает -1, в случае удачи возвращает 0</returns>
	int initialize(int width, int height, const char* title);
	/// <summary>
	/// класс окна
	/// </summary>
	GLFWwindow* window;
public:
	/// <summary>
	/// конструктор - создание окна
	/// </summary>
	/// <param name="width">- ширина окна</param>
	/// <param name="height">- длина окна</param>
	/// <param name="title">- название игры (тайтл)</param>
	Window(int width, int height, const char* title);
	/// <summary>
	/// уничтожение окна.
	/// обязательно это делать в конце программы.
	/// удалять последним делом.
	/// </summary>
	~Window();
	/// <summary>
	/// закрытие окна, но не удаление.
	/// </summary>
	void terminate();
	/// <summary>
	/// окраска окна в определенный цвет по цветовому профилю rgba в диапазоне от 0 до 1 включительно.
	/// </summary>
	/// <param name="red">- красный канал</param>
	/// <param name="green">- зеленый канал</param>
	/// <param name="blue">- синий канал</param>
	/// <param name="alpha">- прозрачность цвета</param>
	void colored(float red, float green, float blue, float alpha);
	void maximize_window();
	/// <summary>
	/// геттер окна
	/// </summary>
	/// <returns>возвращает созданный экземпляр окна</returns>
	GLFWwindow* get_window();
	/// <summary>
	/// смена кадров, работает непосредственно в цикле.
	/// OpenGL использует двойную буферизация – 
	/// "front"-буфер и "back"-буфер – первый отображается, 
	/// а второй в этот момент (вычисляется), поэтому в цикле 
	/// при каждой итерации необходимо менять буферы, чтобы 
	/// "front"-буфер менялся с "back"-буфером.
	/// </summary>
	void swap_buffers();
	/// <summary>
	/// очистка окна после каждого кадра перед рисованием нового.
	/// работает в цикле.
	/// </summary>
	void clear();
	/// <summary>
	/// проверка того, что окно открыто.
	/// </summary>
	/// <returns>возвращает true, если окно открыто, и false в обратном случае</returns>
	bool window_is_closed();
	/// <summary>
	/// вносит в очередь данные о введенных клавишах, 
	/// чтобы GLFW далее регистрировал их, и передавал 
	/// в класс программы.
	/// </summary>
	void poll_events();
	void poll_events_timeout(float timeout);
	/// <summary>
	/// время замены одного кадра на другой.
	/// в зависимости от этого значения рассчитывается, 
	/// какая должна быть разница при изменении положения предметов или камеры.
	/// </summary>
	/// <param name="last">- предыдущая разница во времени</param>
	/// <returns>возвращает значение текущей разницы времени между кадрами</returns>
	static float get_delta_time(float &last);
	/// <summary>
	/// условие выхода из программы при нажатии клавиши Esc.
	/// </summary>
	/// <returns>возвращает true, если метод сработал корректно, и false в обратном случае.</returns>
	bool is_exit();
	/// <summary>
	/// изменение размеров окна
	/// </summary>
	void set_resize();
	/// <summary>
	/// включает буфер глубины, чтобы полигоны, 
	/// стоящие ближе к камере, перекрывали полигоны, стоящие позади.
	/// </summary>
	static void depth_test();
	/// <summary>
	/// отображение только контуров всех объектов
	/// </summary>
	static void polygon_mode();
};
/// <summary>
/// подгон изображения при изменении размера окна
/// </summary>
/// <param name="window">- окно, размер которого был изменен</param>
/// <param name="width">- ширина окна</param>
/// <param name="height">- длина окна</param>
extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);