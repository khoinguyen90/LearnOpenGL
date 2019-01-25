#ifndef POLYGON_H
#define POLYGON_H

#include "Model.h"
#include "glutils.h"
#include "Renderer.h"

class Polygon : public Model
{
private:
	GLfloat vertexAttribute[12] = {
		// Position		// color
		 600.0f,  600.0f,
		 100.0f,  600.0f,
		 100.0f,  100.0f,
		 600.0f,  600.0f,
		 100.0f,  100.0f,
		 600.0f,  100.0f,
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
