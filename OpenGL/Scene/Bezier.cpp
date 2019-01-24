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

	auto resolution = glGetUniformLocation(program->ProgramID, "resolution");
	//auto antialias = glGetUniformLocation(program->ProgramID, "antialias");
	//
	glUniform2f(resolution, 800.0f, 800.0f);
	//glUniform1f(antialias, 4.0f);

    //positionAttribHandle = ProgramManagerObj->ProgramGetVertexAttribLocation(program,(char*)"VertexPosition");
	//colorAttribHandle    = ProgramManagerObj->ProgramGetVertexAttribLocation(program, (char*)"VertexColor");
    
	double d = 64;
	agg::curve4_div P{ d, d, d, 512, 512 - d, 512, 512 - d, d };

	double x, y;
	int order;
	for (int i = 0; i < 64 ; i++)
	{
		order = P.vertex(&x, &y);
		vertexAttribute[i * 2] = x;
		vertexAttribute[i * 2 + 1] = y;
	}

	VertexBuffer vb{ vertexAttribute , sizeof(vertexAttribute) };
	VertexBufferLayout layout;
	layout.Push<float>(2);
	//layout.Push<float>(2);
	//layout.Push<float>(2);
	//layout.Push<float>(1);
	VertexArray va;
	va.AddBuffer(vb, layout);
	
	va.Bind();


	//glEnableVertexAttribArray(positionAttribHandle);
	//glEnableVertexAttribArray(colorAttribHandle);

	//glVertexAttribPointer(positionAttribHandle, 2, GL_FLOAT, false, 0, gTriangleVertices);
	//glVertexAttribPointer(colorAttribHandle, 3, GL_FLOAT, false, 0, gTriangleColors);

    glDrawArrays(GL_POINTS, 0, 64);
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