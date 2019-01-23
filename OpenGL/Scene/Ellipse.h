#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Model.h"
#include "glutils.h"
#include "Renderer.h"

class Ellipse : public Model
{
private:
	GLfloat vertexAttribute[12] = {
		// Position		// color
		 0.5f,  0.5f,
		-0.5f,  0.5f,
		-0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f, -0.5f,
		 0.5f, -0.5f
	};

    GLuint positionAttribHandle;
    GLuint colorAttribHandle;
    GLuint radianAngle;
    
    float degree;
    float radian;

public:
	Ellipse( Renderer* parent = 0);
	~Ellipse();

    void InitModel();
    void Render();

	virtual void TouchEventDown(float x, float y);
	virtual void TouchEventMove(float a, float b);
	virtual void TouchEventRelease(float a, float b);
	
};

#endif // ELLIPSE_H
