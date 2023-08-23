#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>

class Window
{
public:
    GLFWwindow* window;

	int initialize(int width, int height, const char* title);
	void terminate();
	void colored(float red, float green, float blue, float alpha);
	void swap_buffers();
	void clear();
	bool window_is_closed();
	void poll_events();
	static float get_delta_time(float &last);
	bool is_exit();
};