#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>

/// <summary>
/// ����� ���� ���������.
/// ���������� � �������������.
/// ���������������� ������ �����.
/// </summary>
class Window
{
	/// <summary>
	/// ������������� ���� ������ � ���� ������.
	/// </summary>
	/// <param name="width">- ������ ����</param>
	/// <param name="height">- ����� ����</param>
	/// <param name="title">- �������� ���� (�����)</param>
	/// <returns>� ������ ������ ���������� -1, � ������ ����� ���������� 0</returns>
	int initialize(int width, int height, const char* title);
	/// <summary>
	/// ����� ����
	/// </summary>
	GLFWwindow* window;
public:
	/// <summary>
	/// ����������� - �������� ����
	/// </summary>
	/// <param name="width">- ������ ����</param>
	/// <param name="height">- ����� ����</param>
	/// <param name="title">- �������� ���� (�����)</param>
	Window(int width, int height, const char* title);
	/// <summary>
	/// ����������� ����.
	/// ����������� ��� ������ � ����� ���������.
	/// ������� ��������� �����.
	/// </summary>
	~Window();
	/// <summary>
	/// �������� ����, �� �� ��������.
	/// </summary>
	void terminate();
	/// <summary>
	/// ������� ���� � ������������ ���� �� ��������� ������� rgba � ��������� �� 0 �� 1 ������������.
	/// </summary>
	/// <param name="red">- ������� �����</param>
	/// <param name="green">- ������� �����</param>
	/// <param name="blue">- ����� �����</param>
	/// <param name="alpha">- ������������ �����</param>
	void colored(float red, float green, float blue, float alpha);
	void maximize_window();
	/// <summary>
	/// ������ ����
	/// </summary>
	/// <returns>���������� ��������� ��������� ����</returns>
	GLFWwindow* get_window();
	/// <summary>
	/// ����� ������, �������� ��������������� � �����.
	/// OpenGL ���������� ������� ����������� � 
	/// "front"-����� � "back"-����� � ������ ������������, 
	/// � ������ � ���� ������ (�����������), ������� � ����� 
	/// ��� ������ �������� ���������� ������ ������, ����� 
	/// "front"-����� ������� � "back"-�������.
	/// </summary>
	void swap_buffers();
	/// <summary>
	/// ������� ���� ����� ������� ����� ����� ���������� ������.
	/// �������� � �����.
	/// </summary>
	void clear();
	/// <summary>
	/// �������� ����, ��� ���� �������.
	/// </summary>
	/// <returns>���������� true, ���� ���� �������, � false � �������� ������</returns>
	bool window_is_closed();
	/// <summary>
	/// ������ � ������� ������ � ��������� ��������, 
	/// ����� GLFW ����� ������������� ��, � ��������� 
	/// � ����� ���������.
	/// </summary>
	void poll_events();
	void poll_events_timeout(float timeout);
	/// <summary>
	/// ����� ������ ������ ����� �� ������.
	/// � ����������� �� ����� �������� ��������������, 
	/// ����� ������ ���� ������� ��� ��������� ��������� ��������� ��� ������.
	/// </summary>
	/// <param name="last">- ���������� ������� �� �������</param>
	/// <returns>���������� �������� ������� ������� ������� ����� �������</returns>
	static float get_delta_time(float &last);
	/// <summary>
	/// ������� ������ �� ��������� ��� ������� ������� Esc.
	/// </summary>
	/// <returns>���������� true, ���� ����� �������� ���������, � false � �������� ������.</returns>
	bool is_exit();
	/// <summary>
	/// ��������� �������� ����
	/// </summary>
	void set_resize();
	/// <summary>
	/// �������� ����� �������, ����� ��������, 
	/// ������� ����� � ������, ����������� ��������, ������� ������.
	/// </summary>
	static void depth_test();
	/// <summary>
	/// ����������� ������ �������� ���� ��������
	/// </summary>
	static void polygon_mode();
};
/// <summary>
/// ������ ����������� ��� ��������� ������� ����
/// </summary>
/// <param name="window">- ����, ������ �������� ��� �������</param>
/// <param name="width">- ������ ����</param>
/// <param name="height">- ����� ����</param>
extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);