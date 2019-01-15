#pragma once
#include "Model.h"
#include "ProgramManager.h"
#include "Transform.h"
#include <vector>

//! Render Member Data structure
typedef struct
{
	//! Program handler for render
	ProgramManager	ProgramManagerObj;

	//! Transform operation handler
	Transform	TransformObj;

	//! Screen Height
	int screenHeight;

	//! Screen Width
	int screenWidth;

	//! Model List
	std::vector <Model*> models;

	//! Boolean value for to tell system that taping occurs.
	int HorizonHeight;
} RendererData;

class Renderer
{

public:
	//! Default Constructor
	Renderer(void);

	//! Destructor
	~Renderer(void);

	//! Initialize Renderer
	void initializeRenderer();

	//! Return the ProgramManager handler
	inline ProgramManager* RendererProgramManager(){ return &RenderMemData.ProgramManagerObj; }

	//! Return the Transform handler
	inline Transform*  RendererTransform() { return &RenderMemData.TransformObj;  }

	//! Screen Width returned
	inline int screenWidthPixel() { return RenderMemData.screenWidth; }

	//! Screen Height returned
	inline int screenHeightPixel() { return RenderMemData.screenHeight; }

	//! Generate the models
	void createModels();

	//! Render the Models
	void render();

	//! Initializes the Models
	void initializeModels();

	//! Remove all the models
	void clearModels();

	//! Set Project System
	void setUpProjection();

	//! Initializes the Models
	void setUpModels();

	//! Get the model
	Model* getModel( ModelType );

	//! Cache the model
	void addModel( Model* );

	//! resize screen
	void resize( int w, int h );
	static Renderer& Instance()
    {
        static Renderer rendererObj;
        return rendererObj;
    }

	void TouchEventDown(float x, float y);
	void TouchEventMove(float x, float y);
	void TouchEventRelease(float x, float y);
private:
	//! Map render member variable container
	RendererData RenderMemData;
};
