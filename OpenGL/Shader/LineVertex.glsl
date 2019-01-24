#version 330 core

in vec2 a_p0, a_p1;
in vec2 a_normal;

uniform float u_linewidth;
uniform float u_antialias;

out vec2 v_p0, v_p1, v_p;

void main()
{
	vec2 T = normalize(a_p1 - a_p0);
	vec2 O = vec2(-T.y, T.x);

	float l = length(a_p1 - a_p0);
	float t = u_linewidth / 2 + u_antialias;

	vec2 p = a_p0 + (a_normal.x > 0 ? 1 : 0)*l*T + a_normal.y *t* O;

	gl_Position = vec4(p, 0.0, 1.0);
	
	T = vec2(1, 0);
	O = vec2(0, 1);

	v_p0 = vec2(-l/2, 0);
	v_p1 = vec2(l/2, 0);
	v_p = - (v_p0 + (a_normal.x > 0 ? 1 : 0)*l*T + a_normal.y *t* O); // Dont understand why need navigate
	//v_p = (v_p0 + (a_normal.x > 0 ? 1 : 0)*l*T + a_normal.y *t* O);
}
