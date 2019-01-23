#include "Line.h"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "Cache.h"
#include "constant.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

//Note: The Linux is very case sensitive so be aware of specifying correct folder and filename.
#ifdef __APPLE__
#define VERTEX_SHADER_PRG			( char * )"BlueTriangleVertex.glsl"
#define FRAGMENT_SHADER_PRG			( char * )"BlueTriangleFragment.glsl"
#else
#define VERTEX_SHADER_PRG			( char * )"shader/LineVertex.glsl"
#define FRAGMENT_SHADER_PRG			( char * )"shader/LineFragment.glsl"
#endif

// Namespace used
using std::ifstream;
using std::ostringstream;

//GLfloat vertexAttribute[] = {
//	// Position		// color
//	100.0f, 50.0f, 200.0f, 350.0f, -1.0f, -1.0f,50.0f,
//	100.0f, 50.0f, 200.0f, 350.0f, -1.0f, 1.0f, 50.0f,
//	100.0f, 50.0f, 200.0f, 350.0f, 1.0f, -1.0f, 50.0f,
//	100.0f, 50.0f, 200.0f, 350.0f, -1.0f, 1.0f, 50.0f,
//	100.0f, 50.0f, 200.0f, 350.0f, 1.0f, -1.0f, 50.0f,
//	100.0f, 50.0f, 200.0f, 350.0f, 1.0f, 1.0f,  50.0f,
//};

// Global Object Declaration

/*!
	Simple Default Constructor

	\param[in] None.
	\return None

*/
Line::Line( Renderer* parent )
	: Model(parent, this, LineType)
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
Line::~Line()
{
	PROGRAM* program = NULL;
	if ( program = ProgramManagerObj->Program( ( char * )"Line" ) )
	{
		ProgramManagerObj->RemoveProgram(program);
	}
}

/*!
	Initialize the scene, reserve shaders, compile and cache program

	\param[in] None.
	\return None

*/
void Line::InitModel()
{
	if (!(program = ProgramManagerObj->Program( (char*) "Line"))){
		program = ProgramManagerObj->ProgramInit( (char *) "Line" );
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
void Line::Render()
{
    glUseProgram( program->ProgramID );

    radian = degree++/57.2957795;
    
    // Query and send the uniform variable.
    radianAngle          = glGetUniformLocation(program->ProgramID, "RadianAngle");
    glUniform1f(radianAngle, radian);

	//auto resolution = glGetUniformLocation(program->ProgramID, "resolution");
	//auto antialias = glGetUniformLocation(program->ProgramID, "antialias");
	//auto capStyle = glGetUniformLocation(program->ProgramID, "capStyle");
	//
	//glUniform2f(resolution, 800.0f, 800.0f);
	//glUniform1f(antialias, 0.005f);
	//glUniform1f(capStyle, 0.0f);
    
	float thickness = 0.03;
	float antialias = 0.005;

	glm::vec2 startPoint = glm::vec2(0.0, 0.0);
	glm::vec2 endPoint = glm::vec2(0.5, 0.5);

	glm::vec2 T = normalize(endPoint - startPoint);
	glm::vec2 O = glm::vec2(-T.y, T.x);

	//glm::vec2 A0 = startPoint + O * (thickness + antialias);
	//glm::vec2 A1 = startPoint - O * (thickness + antialias);
	//glm::vec2 B0 = endPoint + O * (thickness + antialias);
	//glm::vec2 B1 = endPoint + O * (thickness + antialias);

	auto u_linewidth = glGetUniformLocation(program->ProgramID, "u_linewidth");
	glUniform1f(u_linewidth, thickness + 2 * antialias);

	glm::vec2 A0 = startPoint + O * (thickness + 2 * antialias);
	glm::vec2 A1 = startPoint + (-O) * (thickness + 2 * antialias);
	glm::vec2 B0 = endPoint + O * (thickness + antialias);
	glm::vec2 B1 = endPoint + (-O) * (thickness + antialias);

	float vertexAttribute[]
	{
		startPoint.x, startPoint.y, O.x, O.y,
		startPoint.x, startPoint.y, -O.x, -O.y,
		endPoint.x,  endPoint.y, O.x, O.y,

		endPoint.x, endPoint.y, O.x, O.y,
		startPoint.x, startPoint.y, -O.x, -O.y,
		endPoint.x, endPoint.y, -O.x, -O.y,
	};

	//float vertexAttribute[]
	//{
	//	-0.0f, 0.5f, 0.0, 0.0,
	//	-0.0f, 0.5f, 0.0, 0.0,
	//	 0.0f, 0.5f, 0.0, 0.0,
	//	-0.0f, 0.5f, 0.0, 0.0,
	//	 0.0f, 0.5f, 0.0, 0.0,
	//	 0.0f, 0.5f, 0.0, 0.0
	//};

	VertexBuffer vb{ vertexAttribute , sizeof(vertexAttribute) };
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	//layout.Push<float>(2);
	//layout.Push<float>(1);
	VertexArray va;
	va.AddBuffer(vb, layout);
	
	va.Bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Line::TouchEventDown(float x, float y)
{
	//vertexAttribute[1 * 2 + 0] = 1.0; vertexAttribute[1 * 2 + 1] = 0.0; vertexAttribute[1 * 2 + 2] = 0.0;
	//vertexAttribute[2 * 2 + 3] = 1.0; vertexAttribute[2 * 2 + 4] = 0.0; vertexAttribute[2 * 2 + 5] = 0.0;
	//vertexAttribute[3 * 2 + 6] = 1.0; vertexAttribute[3 * 2 + 7] = 0.0; vertexAttribute[3 * 2 + 8] = 0.0;
}

void Line::TouchEventMove(float x, float y)
{
	//vertexAttribute[1 * 2 + 0] = 0.0; vertexAttribute[1 * 2 + 1] = 1.0; vertexAttribute[1 * 2 + 2] = 0.0;
	//vertexAttribute[2 * 2 + 3] = 0.0; vertexAttribute[2 * 2 + 4] = 1.0; vertexAttribute[2 * 2 + 5] = 0.0;
	//vertexAttribute[3 * 2 + 6] = 0.0; vertexAttribute[3 * 2 + 7] = 1.0; vertexAttribute[3 * 2 + 8] = 0.0;
}

void Line::TouchEventRelease(float x, float y)
{
	//vertexAttribute[1 * 2 + 0] = 0.0; vertexAttribute[1 * 2 + 1] = 0.0; vertexAttribute[1 * 2 + 2] = 1.0;
	//vertexAttribute[2 * 2 + 3] = 0.0; vertexAttribute[2 * 2 + 4] = 0.0; vertexAttribute[2 * 2 + 5] = 1.0;
	//vertexAttribute[3 * 2 + 6] = 0.0; vertexAttribute[3 * 2 + 7] = 0.0; vertexAttribute[3 * 2 + 8] = 1.0;
}