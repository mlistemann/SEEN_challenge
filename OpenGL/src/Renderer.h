#pragma once

#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

#include <memory>

class Renderer
{
private:

public:

	void Draw(const Shader& shader, const VertexArray& vao, const IndexBuffer& ibo) const;
	void Clear() const;
};

