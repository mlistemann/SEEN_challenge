#include "Renderer.h"

void Renderer::Draw(const Shader& shader, const VertexArray& vao, const IndexBuffer& ibo) const
{
	shader.use();

	vao.Bind();
	ibo.Bind();

	glDrawElements(GL_TRIANGLES, ibo.Count(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}