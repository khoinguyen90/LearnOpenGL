#include "Renderer.h"
#include <iostream>
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR) {}
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << " )" << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}

	return true;
}

void Renderer::Clear()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	va.Bind();
	ib.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::DrawLine(unsigned int argb, float startX, float startY, float endX, float endY, float lineWidth)
{
	float lineVertex[] =
	{
		startX, startY,
		endX, endY,
	};
	
	VertexBuffer vb{ &lineVertex, 2 * 2 * sizeof(float) };
	VertexBufferLayout layout;
	layout.Push<float>(2);

	VertexArray va;
	va.AddBuffer(vb, layout);

	m_Shader->SetUniform4f("u_Color",
		(float)((float)((argb >> 24) & 255)/255),
		(float)((float)((argb >> 16) & 255) / 255),
		(float)((float)((argb >> 8) & 255) / 255),
		(float)((float)(argb & 255) / 255));

	//GLCall(glEnable(GL_LINE_SMOOTH));
	GLCall(glLineWidth(lineWidth));
	GLCall(glDrawArrays(GL_LINES, 0, 2));
	//GLCall(glDisable(GL_LINE_SMOOTH));
}
