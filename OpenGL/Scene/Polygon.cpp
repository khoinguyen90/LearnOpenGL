#include "Polygon.h"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "Cache.h"
#include "constant.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

//Note: The Linux is very case sensitive so be aware of specifying correct folder and filename.
#ifdef __APPLE__
#define VERTEX_SHADER_PRG			( char * )"BlueTriangleVertex.glsl"
#define FRAGMENT_SHADER_PRG			( char * )"BlueTriangleFragment.glsl"
#else
#define VERTEX_SHADER_PRG			( char * )"shader/PolygonVertex.glsl"
#define FRAGMENT_SHADER_PRG			( char * )"shader/PolygonFragment.glsl"
#endif

// Namespace used
using std::ifstream;
using std::ostringstream;

//GLfloat vertexAttribute[] = {
//	// Position		// color
//	100.0f, 50.0f, 200.0f, 350.0f, 0.0f, 0.0f, 10.0f,
//	100.0f, 50.0f, 200.0f, 350.0f, 0.0f, 1.0f, 10.0f,
//	100.0f, 50.0f, 200.0f, 350.0f, 1.0f, 0.0f, 10.0f,
//	100.0f, 50.0f, 200.0f, 350.0f, 0.0f, 1.0f, 10.0f,
//	100.0f, 50.0f, 200.0f, 350.0f, 1.0f, 0.0f, 10.0f,
//	100.0f, 50.0f, 200.0f, 350.0f, 1.0f, 1.0f, 10.0f,
//};

// Global Object Declaration

/*!
	Simple Default Constructor

	\param[in] None.
	\return None

*/
Polygon::Polygon(Renderer* parent)
	: Model(parent, this, TriangleType)
{
	if (!parent)
		return;

	RendererHandler = parent;
	ProgramManagerObj = parent->RendererProgramManager();
	TransformObj = parent->RendererTransform();
	degree = 0;
}


/*!
	Simple Destructor

	\param[in] None.
	\return None

*/
Polygon::~Polygon()
{
	PROGRAM* program = NULL;
	if (program = ProgramManagerObj->Program((char *)"Polygon"))
	{
		ProgramManagerObj->RemoveProgram(program);
	}
}

/*!
	Initialize the scene, reserve shaders, compile and cache program

	\param[in] None.
	\return None

*/
void Polygon::InitModel()
{
	if (!(program = ProgramManagerObj->Program((char*) "Polygon"))) {
		program = ProgramManagerObj->ProgramInit((char *) "Polygon");
		ProgramManagerObj->AddProgram(program);
	}

	program->VertexShader = ShaderManager::ShaderInit(VERTEX_SHADER_PRG, GL_VERTEX_SHADER);
	program->FragmentShader = ShaderManager::ShaderInit(FRAGMENT_SHADER_PRG, GL_FRAGMENT_SHADER);

	//////////////////////////////////////////////////////
	/////////// Vertex shader //////////////////////////
	//////////////////////////////////////////////////////
	CACHE *m = reserveCache(VERTEX_SHADER_PRG, true);

	if (m) {
		if (!ShaderManager::ShaderCompile(program->VertexShader, (char *)m->buffer, 1)) exit(1);
	}
	m = freeCache(m);

	m = reserveCache(FRAGMENT_SHADER_PRG, true);
	if (m) {
		if (!ShaderManager::ShaderCompile(program->FragmentShader, (char *)m->buffer, 1)) exit(2);
	}
	m = freeCache(m);

	if (!ProgramManagerObj->ProgramLink(program, 1)) exit(3);

	glUseProgram(program->ProgramID);

	return;
}

/*!
	Initialize the scene, reserve shaders, compile and cache program

	\param[in] None.
	\return None

*/
void Polygon::Render()
{
	glUseProgram(program->ProgramID);

	auto u_resolution = glGetUniformLocation(program->ProgramID, "u_resolution");
	auto u_lineWidth = glGetUniformLocation(program->ProgramID, "u_lineWidth");
	auto u_lineLength = glGetUniformLocation(program->ProgramID, "u_lineLength");

	glUniform2f(u_resolution, 800.0f, 800.0f);
	glUniform1f(u_lineWidth, 5);
	glUniform1f(u_lineLength, 1350);

	unsigned int indexBuffer[] = {
		0, 1, 2,
		1, 2, 3,

		4, 5, 6,
		5, 6, 7,

		8, 9, 10,
		9, 10, 11,
	};
	IndexBuffer ib{ indexBuffer , 6 * 3 };
	VertexBuffer vb{ vertexAttribute , sizeof(vertexAttribute) };
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(4);
	layout.Push<float>(3);

	VertexArray va;
	va.AddBuffer(vb, layout);
	va.Bind();
	ib.Bind();

	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
}

void Polygon::TouchEventDown(float x, float y)
{
	//vertexAttribute[1 * 2 + 0] = 1.0; vertexAttribute[1 * 2 + 1] = 0.0; vertexAttribute[1 * 2 + 2] = 0.0;
	//vertexAttribute[2 * 2 + 3] = 1.0; vertexAttribute[2 * 2 + 4] = 0.0; vertexAttribute[2 * 2 + 5] = 0.0;
	//vertexAttribute[3 * 2 + 6] = 1.0; vertexAttribute[3 * 2 + 7] = 0.0; vertexAttribute[3 * 2 + 8] = 0.0;
}

void Polygon::TouchEventMove(float x, float y)
{
	vertexAttribute[1 * 2 + 0] = 0.0; vertexAttribute[1 * 2 + 1] = 1.0; vertexAttribute[1 * 2 + 2] = 0.0;
	vertexAttribute[2 * 2 + 3] = 0.0; vertexAttribute[2 * 2 + 4] = 1.0; vertexAttribute[2 * 2 + 5] = 0.0;
	vertexAttribute[3 * 2 + 6] = 0.0; vertexAttribute[3 * 2 + 7] = 1.0; vertexAttribute[3 * 2 + 8] = 0.0;
}

void Polygon::TouchEventRelease(float x, float y)
{
	//vertexAttribute[1 * 2 + 0] = 0.0; vertexAttribute[1 * 2 + 1] = 0.0; vertexAttribute[1 * 2 + 2] = 1.0;
	//vertexAttribute[2 * 2 + 3] = 0.0; vertexAttribute[2 * 2 + 4] = 0.0; vertexAttribute[2 * 2 + 5] = 1.0;
	//vertexAttribute[3 * 2 + 6] = 0.0; vertexAttribute[3 * 2 + 7] = 0.0; vertexAttribute[3 * 2 + 8] = 1.0;
}