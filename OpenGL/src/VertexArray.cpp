#include "VertexArray.h"

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::SetVertexBuffer(const VertexBuffer& vbo, const int componentsSize) const
{
	glBindVertexArray(m_RendererID);
	vbo.Bind();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, componentsSize, GL_FLOAT, GL_FALSE, componentsSize * sizeof(float), 0);
}