#ifndef BEZIER_H
#define BEZIER_H

#include "Model.h"
#include "glutils.h"
#include "Renderer.h"

class Bezier : public Model
{
private:
	GLfloat vertexAttribute[16 * 60];// =
	//{
	//	// P1				// P2						// P3				
	//	0.0, 0.0,			0.0, 0.0,  1.0, 0.0,		50.0, 500.0,
	//	0.0, 0.0,			0.0, 0.0, -1.0, 0.0,		50.0, 500.0,

	//	0.0, 0.0,			50.0, 500.0, 1.0, 450,		500.0, 500.0,
	//	0.0, 0.0,			50.0, 500.0, -1.0, 450,		500.0, 500.0,

	//	50.0, 500.0,		500.00, 500.00,  1.0, 900.0,	500.0, 50.0,
	//	50.0, 500.0,		500.00, 500.00, -1.0, 900.0,	500.0, 50.0,

	//	500.00, 500.00,		500.0, 50.0,  1.0, 1350.0,		500.0, 50.0,
	//	500.00, 500.00,		500.0, 50.0, -1.0, 1350.0,		500.0, 50.0,
	//};

    GLuint positionAttribHandle;
    GLuint colorAttribHandle;
    GLuint radianAngle;
    
    float degree;
    float radian;

public:
    Bezier( Renderer* parent = 0);
	~Bezier();

    void InitModel();
    void Render();

	virtual void TouchEventDown(float x, float y);
	virtual void TouchEventMove(float a, float b);
	virtual void TouchEventRelease(float a, float b);
	
};

#endif // BEZIER_H
