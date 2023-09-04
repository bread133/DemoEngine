#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>

class Window
{
	int initialize(int width, int height, const char* title);
public:
    GLFWwindow* window;

	Window(int width, int height, const char* title);
	~Window();
	void terminate();
	void colored(float red, float green, float blue, float alpha);
	void swap_buffers();
	void clear();
	bool window_is_closed();
	void poll_events();
	static float get_delta_time(float &last);
	bool is_exit();
	void set_resize();
	static void depth_test();
	static void polygon_mode();
};

extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);