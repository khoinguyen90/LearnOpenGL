#ifndef LINE_H
#define LINE_H

#include "Model.h"
#include "glutils.h"
#include "Renderer.h"

class Line : public Model
{
private:

    GLuint positionAttribHandle;
    GLuint colorAttribHandle;
    GLuint radianAngle;
    
    float degree;
    float radian;

public:
	Line( Renderer* parent = 0);
	~Line();

    void InitModel();
    void Render();

	virtual void TouchEventDown(float x, float y);
	virtual void TouchEventMove(float a, float b);
	virtual void TouchEventRelease(float a, float b);
	
};

#endif // LINE_H
