#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void * data, GLuint size)
{
	// (how many buffers to create, pointer to the buffer)
	glGenBuffers(1, &m_RendererID);
	// (target, the actual buffer)
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	// FILL THE BUFFER WITH DATA
	// (target, size of the buffer, pointer to the data, hint for OpenGL how drawing will be used)
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}