#pragma once

class GLFWwindow;

class Window
{
	static GLFWwindow* window;
public:
	static int initialize(int width, int height, const char* title);
	static void terminate();
	static void colored(float red, float green, float blue, float alpha);
	static void swap_buffers();
	static void clear();
	static bool window_is_closed();
	static void poll_events();
};