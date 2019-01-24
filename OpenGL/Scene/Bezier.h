#ifndef BEZIER_H
#define BEZIER_H

#include "Model.h"
#include "glutils.h"
#include "Renderer.h"

class Bezier : public Model
{
private:
	GLfloat vertexAttribute[128];
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
