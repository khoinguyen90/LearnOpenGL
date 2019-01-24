#include "Renderer.h"
#include "Triangle.h"
#include "Cube.h"
#include "Ellipse.h"
#include "Line.h"
#include "Bezier.h"

Renderer::Renderer(void)
{
}

Renderer::~Renderer(void)
{
}

void Renderer::initializeRenderer()
{
	LOGI("initializeRenderer");
	setUpModels();
}

void Renderer::createModels()
{
	clearModels();

	//Add your custom models here.
	addModel( new Bezier	( this ) );
}

/*!
	Remove all the Model classes from the Renderer.

	\param[in] None.

	\return None.
*/
void Renderer::clearModels()
{
	for( int i=0; i<RenderMemData.models.size();  i++ ){
		delete RenderMemData.models.at(i);
	}
	RenderMemData.models.clear();
}

/*!
	Setup of the view port and projection initialization. In projection initialization the Ortho or Perspective is set
	as per requirement.

	\param[in] width of the screen.
	\param[in] height of the screen.

	\return void.
*/
void Renderer::setUpProjection()
{
	ProgramManager* ProgramManagerObj = &RenderMemData.ProgramManagerObj;
	Transform*	TransformObj  = &RenderMemData.TransformObj;

	TransformObj->TransformInit();

	TransformObj->TransformSetMatrixMode( PROJECTION_MATRIX );

	TransformObj->TransformLoadIdentity();

	TransformObj->TransformOrtho( -10, 10, -10, 10, -10, 10 );

	//TransformObj->TransformSetPerspective(80.0f, 1, 1.0, 100, 0);
	TransformObj->TransformSetMatrixMode( VIEW_MATRIX );
	TransformObj->TransformLoadIdentity();

	TransformObj->TransformSetMatrixMode( MODEL_MATRIX );
	TransformObj->TransformLoadIdentity();
}

/*!
	Setup of the view port and projection initialization. In projection initialization the Ortho or Perspective is set
	as per requirement.

	\param[in] width of the screen.
	\param[in] height of the screen.

	\return void.
*/
void Renderer::resize(int w, int h)
{
	RenderMemData.screenWidth		= w;
	RenderMemData.screenHeight		= h;
	glViewport( 0, 0, w, h );
}

/*!
	Create and Initializes all models.

	\param[in] void.

	\return void.
*/
void Renderer::setUpModels()
{
	// ! Generate the models and cache all
	createModels();

	//! Do the init stuff as per model requirements
	initializeModels();
}

/*!
	This returns the model renderer of the model. A Model renderer is basically a class responsible for managing the same type of models.

	\param[in] type Enumeration of the model type want to query.

	\return Model pointer.
*/
Model* Renderer::getModel( ModelType type)
{
	for( int i=0; i<RenderMemData.models.size();  i++ )
	{
		Model* model = RenderMemData.models.at(i);

		if ( model->GetModelType() == type )
			return model;
	}

	return NULL;
}

/*!
	This function is responsible for adding a model in the Renderer model vector.
	The Renderer handle all the models from a unique vector based list.

	\param[in] Model pointer of the Model user want to add.

	\return None.
*/
void Renderer::addModel(Model* model)
{
	RenderMemData.models.push_back( model );
}

/*!
	Performs initializing of all the models this may include setup for shaders their caching.
	rendering for each model, creation and caching of IBO, VBO, FBO etc.

	\param[in] void.

	\return void.
*/
void Renderer::initializeModels()
{
	for( int i=0; i<RenderMemData.models.size();  i++ )
		RenderMemData.models.at(i)->InitModel();
}

/*!
	Performs rendering for each model

	\param[in] void.

	\return void.
*/
void Renderer::render()
{
	for( int i=0; i<RenderMemData.models.size();  i++ ){
		RenderMemData.models.at(i)->Render();
	}
}

void Renderer::TouchEventDown(float x, float y)
{
	for (int i = 0; i < RenderMemData.models.size(); i++)
	{
		RenderMemData.models.at(i)->TouchEventDown(x, y);
	}
}

void Renderer::TouchEventMove(float x, float y)
{
	for (int i = 0; i < RenderMemData.models.size(); i++)
	{
		RenderMemData.models.at(i)->TouchEventMove(x, y);
	}
}

void Renderer::TouchEventRelease(float x, float y)
{
	for (int i = 0; i < RenderMemData.models.size(); i++)
	{
		RenderMemData.models.at(i)->TouchEventRelease(x, y);
	}
}