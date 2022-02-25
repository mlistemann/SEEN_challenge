#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"

#include <iostream>
#include <array>
#include <vector>
#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main(void)
{
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "SEEN OpenGL", NULL, NULL);
	if (!window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader shader("res/shaders/shader.vert", "res/shaders/shader.frag");

	// DATA
	std::array<float, 8> quad = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};

	unsigned int quadIndices[]{
		0, 1, 2,
		2, 3, 0 };

	// GPU BUFFER
	VertexBuffer VBO(quad.data(), quad.size() * sizeof(float));
	IndexBuffer IBO(quadIndices, 6);
	VertexArray VAO;

	VAO.SetVertexBuffer(VBO, 2);
	VAO.Unbind();

	float redChannel = 1.0f;

	Renderer renderer;

	// RENDER LOOP
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		shader.use();

		// TRANSFORMATION MATRICES
		/*glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);*/

		/*shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);*/

		shader.setFloat("u_Color", redChannel);

		renderer.draw(shader, VAO, IBO);
		
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
		
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}