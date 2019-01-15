#version 330 core

in vec4 VertexPosition, VertexColor;
out vec4 VarColor;
uniform mat4 MODELVIEWPROJECTIONMATRIX;

void main()
{
	gl_Position = MODELVIEWPROJECTIONMATRIX * VertexPosition;
	VarColor = VertexColor;
}