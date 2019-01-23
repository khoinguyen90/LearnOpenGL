#version 330 core

uniform vec2 resolution;
in vec2 position;
out vec2 v_position;
void main()
{
    v_position = position;
    gl_Position = vec4(position , 0.0, 1.0);
}