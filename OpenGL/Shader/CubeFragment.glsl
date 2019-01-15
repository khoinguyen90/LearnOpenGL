#version 330 core

in vec4 VarColor;
out vec4 FragColor;

void main()
{
	FragColor = vec4(VarColor.x, VarColor.y, VarColor.z, 1.0f);
}