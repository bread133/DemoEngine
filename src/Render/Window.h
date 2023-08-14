#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>

class Window
{
public:
	static GLFWwindow* window;

	static int initialize(int width, int height, const char* title);
	static void terminate();
	static void colored(float red, float green, float blue, float alpha);
	static void swap_buffers();
	static void clear();
	static bool window_is_closed();
	static void poll_events();
	static float get_delta_time(float &last);
};