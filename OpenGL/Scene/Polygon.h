#ifndef POLYGON_H
#define POLYGON_H

#include "Model.h"
#include "glutils.h"
#include "Renderer.h"

class Polygon : public Model
{
private:
	glm::vec2 p0 { 40, 40 };
	glm::vec2 p1 { 200, 500 };
	glm::vec2 p2 { 500, 200 };
	glm::vec2 p3 { 500, 500 };

	float vertexBorder[12 * 11] =
	{
		p0.x, p0.y, p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, -1.0f,  1.0f, 0,
		p0.x, p0.y, p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, -1.0f, -1.0f, 0,
		p0.x, p0.y, p0.x, p0.y, p1.x, p1.y, p2.x, p2.y,  1.0f,  1.0f, 0,
		p0.x, p0.y, p0.x, p0.y, p1.x, p1.y, p2.x, p2.y,  1.0f, -1.0f, 0,

		p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, -1.0f,  1.0f, glm::length(p1 - p0),
		p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, -1.0f, -1.0f, glm::length(p1 - p0),
		p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y,  1.0f,  1.0f, glm::length(p1 - p0),
		p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y,  1.0f, -1.0f, glm::length(p1 - p0),

		p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p3.x, p3.y, -1.0f,  1.0f, glm::length(p1 - p0) + glm::length(p2 - p1),
		p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p3.x, p3.y,	-1.0f, -1.0f, glm::length(p1 - p0) + glm::length(p2 - p1),
		p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p3.x, p3.y,	 1.0f,  1.0f, glm::length(p1 - p0) + glm::length(p2 - p1),
		p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p3.x, p3.y,	 1.0f, -1.0f, glm::length(p1 - p0) + glm::length(p2 - p1),
	};

	float vertexFillter[12]
	{
		p0.x, p0.y, p1.x, p1.y, p2.x, p2.y,
		p0.x, p0.y, p2.x, p2.y, p3.x, p3.y,
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
