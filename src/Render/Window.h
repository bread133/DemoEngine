#pragma once

class GLFWwindow;
class Window
{
public:
	static int initialize(int width, int height, const char* title);
	static void terminate();
	static void colored(float red, float green, float blue, float alpha);
	static void swap_buffers();
};

