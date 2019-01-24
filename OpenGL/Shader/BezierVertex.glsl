#version 330 core

uniform vec2 resolution;
in vec2 position;
out vec2 v_position;
void main()
{
	gl_PointSize = 10;
    v_position = position;
    gl_Position = vec4(2 * position / resolution - 1.0, 0.0, 1.0);
}