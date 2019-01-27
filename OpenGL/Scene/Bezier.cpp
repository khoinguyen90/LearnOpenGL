#include "Bezier.h"

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

#include "curve4_div.h"

//Note: The Linux is very case sensitive so be aware of specifying correct folder and filename.
#ifdef __APPLE__
#define VERTEX_SHADER_PRG			( char * )"BlueTriangleVertex.glsl"
#define FRAGMENT_SHADER_PRG			( char * )"BlueTriangleFragment.glsl"
#else
#define VERTEX_SHADER_PRG			( char * )"shader/BezierVertex.glsl"
#define FRAGMENT_SHADER_PRG			( char * )"shader/BezierFragment.glsl"
#endif

// Namespace used
using std::ifstream;
using std::ostringstream;

// Global Object Declaration

/*!
	Simple Default Constructor

	\param[in] None.
	\return None

*/
Bezier::Bezier( Renderer* parent )
	: Model(parent, this, TriangleType)
{
	if (!parent)
		return;

	RendererHandler		= parent;
	ProgramManagerObj	= parent->RendererProgramManager();
	TransformObj		= parent->RendererTransform();
    degree              = 0;
}


/*!
	Simple Destructor

	\param[in] None.
	\return None

*/
Bezier::~Bezier()
{
	PROGRAM* program = NULL;
	if ( program = ProgramManagerObj->Program( ( char * )"Bezier" ) )
	{
		ProgramManagerObj->RemoveProgram(program);
	}
}

/*!
	Initialize the scene, reserve shaders, compile and cache program

	\param[in] None.
	\return None

*/
void Bezier::InitModel()
{
	if (!(program = ProgramManagerObj->Program( (char*) "Bezier"))){
		program = ProgramManagerObj->ProgramInit( (char *) "Bezier" );
		ProgramManagerObj->AddProgram( program );
	}

	program->VertexShader	= ShaderManager::ShaderInit( VERTEX_SHADER_PRG,	GL_VERTEX_SHADER	);
	program->FragmentShader	= ShaderManager::ShaderInit( FRAGMENT_SHADER_PRG, GL_FRAGMENT_SHADER	);

    //////////////////////////////////////////////////////
    /////////// Vertex shader //////////////////////////
    //////////////////////////////////////////////////////
	CACHE *m = reserveCache( VERTEX_SHADER_PRG, true );

	if( m ) {
		if( !ShaderManager::ShaderCompile( program->VertexShader, ( char * )m->buffer, 1 ) ) exit( 1 );
	}
	m = freeCache( m );

	m = reserveCache( FRAGMENT_SHADER_PRG, true );
	if( m ) {
		if( !ShaderManager::ShaderCompile( program->FragmentShader, ( char * )m->buffer, 1 ) ) exit( 2 );
	}
	m = freeCache( m );

    if( !ProgramManagerObj->ProgramLink( program, 1 ) ) exit( 3 );

    glUseProgram( program->ProgramID );

    return;
}

/*!
	Initialize the scene, reserve shaders, compile and cache program

	\param[in] None.
	\return None

*/
void Bezier::Render()
{
    glUseProgram( program->ProgramID );

    //radian = degree++/57.2957795;
    
    // Query and send the uniform variable.
    //radianAngle          = glGetUniformLocation(program->ProgramID, "RadianAngle");
    //glUniform1f(radianAngle, radian);

	auto u_resolution = glGetUniformLocation(program->ProgramID, "u_resolution");
	auto u_lineWidth = glGetUniformLocation(program->ProgramID, "u_lineWidth");
	auto u_lineLength = glGetUniformLocation(program->ProgramID, "u_lineLength");
	//auto antialias = glGetUniformLocation(program->ProgramID, "antialias");
	//
	glUniform2f(u_resolution, 800.0f, 800.0f);
	glUniform1f(u_lineWidth, 10);
	glUniform1f(u_lineLength, 1350);
    
	double d = 10;
	agg::curve4_div P{ d, d, d, 700, 200 - d, 512, 512 - d, d };

	double p1X, p1Y, p2X, p2Y, p3X, p3Y;
	double lengh = 0;

	for (int i = 0; i < 60 ; i++)
	{
		if (i == 0)
		{
			P.vertex(&p1X, &p1Y);
			p2X = p1X;
			p2Y = p1Y;
			P.vertex(&p3X, &p3Y);
		}
		else
		{
			p1X = p2X;
			p1Y = p2Y;
			p2X = p3X;
			p2Y = p3Y;
			P.vertex(&p3X, &p3Y);
		}

		vertexAttribute[i * 16 + 0] = p1X;
		vertexAttribute[i * 16 + 1] = p1Y;
		vertexAttribute[i * 16 + 2] = p2X;
		vertexAttribute[i * 16 + 3] = p2Y;
		vertexAttribute[i * 16 + 4] = 1;
		vertexAttribute[i * 16 + 5] = 0;
		vertexAttribute[i * 16 + 6] = p3X;
		vertexAttribute[i * 16 + 7] = p3Y;

		vertexAttribute[i * 16 + 8] = p1X;
		vertexAttribute[i * 16 + 9] = p1Y;
		vertexAttribute[i * 16 + 10] = p2X;
		vertexAttribute[i * 16 + 11] = p2Y;
		vertexAttribute[i * 16 + 12] = -1;
		vertexAttribute[i * 16 + 13] = 0;
		vertexAttribute[i * 16 + 14] = p3X;
		vertexAttribute[i * 16 + 15] = p3Y;

		// Start lengh
		//vertexAttribute[i * 11 + 1] = lengh;

		// Start length for next line
		//lengh += glm::length(glm::vec2(p2X, p2Y) - glm::vec2(p1X, p1Y));
	}

	VertexBuffer vb{ vertexAttribute , sizeof(vertexAttribute) };
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(4);
	layout.Push<float>(2);
	//layout.Push<float>(2);
	//layout.Push<float>(2);
	//layout.Push<float>(1);

	//unsigned int indices[64 * 3];
	//for (int i = 0; i < 64; i++)
	//{
	//	indices[i * 3] = 3 * i;
	//	indices[i * 3 + 1] = i * 3 + 1;
	//	indices[i * 3 + 2] = i * 3 + 2;
	//}

	//unsigned int indices[6] = {
	//	0, 1, 2,
	//	2, 1, 3,


	//};

	//IndexBuffer index{ indices , 6 };
	VertexArray va;
	va.AddBuffer(vb, layout);
	
	//index.Bind();
	va.Bind();

	//glEnableVertexAttribArray(positionAttribHandle);
	//glEnableVertexAttribArray(colorAttribHandle);

	//glVertexAttribPointer(positionAttribHandle, 2, GL_FLOAT, false, 0, gTriangleVertices);
	//glVertexAttribPointer(colorAttribHandle, 3, GL_FLOAT, false, 0, gTriangleColors);

	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 60 * 2);
}

void Bezier::TouchEventDown(float x, float y)
{
	//vertexAttribute[1 * 2 + 0] = 1.0; vertexAttribute[1 * 2 + 1] = 0.0; vertexAttribute[1 * 2 + 2] = 0.0;
	//vertexAttribute[2 * 2 + 3] = 1.0; vertexAttribute[2 * 2 + 4] = 0.0; vertexAttribute[2 * 2 + 5] = 0.0;
	//vertexAttribute[3 * 2 + 6] = 1.0; vertexAttribute[3 * 2 + 7] = 0.0; vertexAttribute[3 * 2 + 8] = 0.0;
}

void Bezier::TouchEventMove(float x, float y)
{
	vertexAttribute[1 * 2 + 0] = 0.0; vertexAttribute[1 * 2 + 1] = 1.0; vertexAttribute[1 * 2 + 2] = 0.0;
	vertexAttribute[2 * 2 + 3] = 0.0; vertexAttribute[2 * 2 + 4] = 1.0; vertexAttribute[2 * 2 + 5] = 0.0;
	vertexAttribute[3 * 2 + 6] = 0.0; vertexAttribute[3 * 2 + 7] = 1.0; vertexAttribute[3 * 2 + 8] = 0.0;
}

void Bezier::TouchEventRelease(float x, float y)
{
	//vertexAttribute[1 * 2 + 0] = 0.0; vertexAttribute[1 * 2 + 1] = 0.0; vertexAttribute[1 * 2 + 2] = 1.0;
	//vertexAttribute[2 * 2 + 3] = 0.0; vertexAttribute[2 * 2 + 4] = 0.0; vertexAttribute[2 * 2 + 5] = 1.0;
	//vertexAttribute[3 * 2 + 6] = 0.0; vertexAttribute[3 * 2 + 7] = 0.0; vertexAttribute[3 * 2 + 8] = 1.0;
}