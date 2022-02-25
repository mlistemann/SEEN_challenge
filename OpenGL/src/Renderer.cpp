#include "Renderer.h"

void Renderer::draw(const Shader& shader, const VertexArray& vao, const IndexBuffer& ibo) const
{
	shader.use();

	vao.Bind();
	ibo.Bind();

	glDrawElements(GL_TRIANGLES, ibo.Count(), GL_UNSIGNED_INT, nullptr);
}