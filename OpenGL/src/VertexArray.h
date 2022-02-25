#pragma once

#include <memory>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void SetVertexBuffer(const VertexBuffer& vbo, const int componentsSize) const;
private:
	GLuint m_RendererID;
};

