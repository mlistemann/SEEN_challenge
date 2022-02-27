#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Renderer.h"

class Window
{
private:
	GLFWwindow* m_window;
	size_t m_width;
	size_t m_height;
	std::string m_name;

public:
	Window();
	Window(const size_t width, const size_t height, const std::string& name);

	bool ShouldClose() const;
	void Update() const;
	void ProcessInput() const;

	~Window();
};

