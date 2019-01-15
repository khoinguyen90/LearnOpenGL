#ifndef CUBE_H
#define CUBE_H

#include "Model.h"
#include "glutils.h"
#include "Renderer.h"

class Cube : public Model
{
private:
	GLuint vId;
	GLuint iId;
	GLuint Vertex_VAO_Id;
	int size;

public:
	Cube(Renderer* parent = 0);
	~Cube();

	void InitModel();

	void Render();
	void RenderCubeOfCubes();
	void RenderCube();
	void TouchEventDown(float x, float y);
};

#endif // CUBE_H
