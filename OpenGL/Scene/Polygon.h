#ifndef POLYGON_H
#define POLYGON_H

#include "Model.h"
#include "glutils.h"
#include "Renderer.h"

class Polygon : public Model
{
private:
	GLfloat vertexAttribute[12 * 9] =
	{
		// P1				// P2								// P3				
		50.0, 50.0,			50.0, 50.0,  1.0, -1.0, 0.0,		300.0, 500.0,
		50.0, 50.0,			50.0, 50.0, -1.0, -1.0, 0.0,		300.0, 500.0,

		50.0, 50.0,			300.0, 500.0, 1.0,  1.0, 450,		200.0, 50.0,
		50.0, 50.0,			300.0, 500.0, -1.0, 1.0, 450,		200.0, 50.0,

		50.0, 50.0,			300.0, 500.0, 1.0,  -1.0, 450,		200.0, 50.0,
		50.0, 50.0,			300.0, 500.0, -1.0, -1.0, 450,		200.0, 50.0,

		300.0, 500.0,		200.0, 50.0,  1.0, 1.0, 900.0,		500.0, 50.0,
		300.0, 500.0,		200.0, 50.0, -1.0, 1.0, 900.0,		500.0, 50.0,

		300.0, 500.0,		200.0, 50.0,  1.0, -1.0, 900.0,		500.0, 50.0,
		300.0, 500.0,		200.0, 50.0, -1.0, -1.0, 900.0,		500.0, 50.0,

		200.0, 50.0,		500.0, 50.0,  1.0, 1.0, 1350.0,		500.0, 50.0,
		200.0, 50.0,		500.0, 50.0, -1.0, 1.0, 1350.0,		500.0, 50.0,
	};

	GLuint positionAttribHandle;
	GLuint colorAttribHandle;
	GLuint radianAngle;

	float degree;
	float radian;

public:
	Polygon(Renderer* parent = 0);
	~Polygon();

	void InitModel();
	void Render();

	virtual void TouchEventDown(float x, float y);
	virtual void TouchEventMove(float a, float b);
	virtual void TouchEventRelease(float a, float b);

};

#endif // SCENEBASIC_H
