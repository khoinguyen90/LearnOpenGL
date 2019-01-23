#version 330 core

in vec2 a_position;
in vec2 a_normal;

uniform float u_linewidth;

void main()
{
	gl_Position = vec4(a_position + a_normal * u_linewidth, 0, 1);
}
