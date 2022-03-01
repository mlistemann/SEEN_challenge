#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Window.h"

#include <iostream>
#include <array>
#include <vector>
#include <string>

int main(void)
{
	Window window(1920, 1080, "Seen OpenGL");

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

	Renderer renderer;

	float xTranslate = 0.0f;
	float increment = 0.05f;

	float aspectRatio = (float)window.GetWidth() / (float)window.GetHeight();
	// RENDER LOOP
	while (!window.ShouldClose())
	{
		window.ProcessInput();

		renderer.Clear();		

		{
			// DRAW FIRST QUAD
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.0f));
			glm::mat4 view = glm::mat4(1.0f);
			view = glm::translate(view, glm::vec3(xTranslate, 0.6f, 0.0f));
			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f);

			shader.use();
			shader.setMat4("model", model);
			shader.setMat4("view", view);
			shader.setMat4("projection", projection);

			shader.setVec3("u_Color", glm::vec3(0.0, 0.0, 1.0));

			renderer.Draw(shader, VAO, IBO);
		}

		{
			// DRAW SECOND QUAD
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.0f));
			glm::mat4 view = glm::mat4(1.0f);
			view = glm::translate(view, glm::vec3(-xTranslate, -0.6f, 0.0f));
			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f);

			shader.use();
			shader.setMat4("model", model);
			shader.setMat4("view", view);
			shader.setMat4("projection", projection);

			shader.setVec3("u_Color", glm::vec3(1.0, 0.0, 0.0));

			renderer.Draw(shader, VAO, IBO);

		}

		if (xTranslate > (aspectRatio * 1.0f))
			increment -= 0.05f;
		else if (xTranslate < (aspectRatio * -1.0f))
			increment += 0.05f;

		xTranslate += increment;

		window.Update();
	}

	return 0;
}