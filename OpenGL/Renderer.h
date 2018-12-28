#pragma once

#include <GL/glew.h>
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

#define ASSERT(x)	if(!(x)) __debugbreak();
#define GLCall(x)   GLClearError();\
					x;\
					ASSERT(GLLogCall(#x, __FILE__, __LINE__));


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
private:
	Shader * m_Shader;
public:
	Renderer(Shader *shader) : m_Shader(shader) {}
	void Clear();
	void DrawLine(unsigned int argb, float startX, float startY, float endX, float endY, float lineWidth);
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
};