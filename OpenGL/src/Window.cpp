#include "Window.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::Window() :
	m_window(nullptr), m_width(1280), m_height(720), m_name("Hello OpenGL")
{
}

Window::Window(const size_t width, const size_t height, const std::string& name) :
	m_window(nullptr), m_width(width), m_height(height), m_name(name)
{
	if (!glfwInit())
	{
		throw "Could not initialize GLFW";
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	m_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		throw "Could not create a window";
	}

	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	glfwSwapInterval(2);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		throw "Failed to initialize GLAD";
	}
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_window);
}

void Window::Update() const
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void Window::ProcessInput() const
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
}