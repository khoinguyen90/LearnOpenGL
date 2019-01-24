#version 330 core

#define ANTIALIAS					2

#define CAP_STYLE_FLAT				0
#define CAP_STYLE_ROUND				1
#define CAP_STYLE_ARROW				2
#define CAP_STYLE_FILLEDARROW		3

in vec2 a_p0, a_p1;
in vec2 a_normal;
in vec4 a_color;

uniform int u_linewidth;
uniform int u_p0CapSize;
uniform int u_p1CapSize;
uniform int u_p0CapStyle;
uniform int u_p1CapStyle;
uniform ivec2 resolution;

out vec2 v_p0, v_p1, v_p;
out vec4 v_color;
out float v_antialias, startP0CapX, startP1CapX;

void main()
{
	startP0CapX = - ((u_linewidth / 2) + ANTIALIAS);
	startP1CapX = ((u_linewidth / 2) + ANTIALIAS);

	v_antialias = ANTIALIAS;
	vec2 T = normalize(a_p1 - a_p0);
	vec2 O = vec2(-T.y, T.x);

	int u_capSize = 0;
	float l = length(a_p1 - a_p0);
	if(u_p0CapStyle == CAP_STYLE_ARROW || u_p0CapStyle == CAP_STYLE_FILLEDARROW
		|| u_p1CapStyle == CAP_STYLE_ARROW || u_p1CapStyle == CAP_STYLE_FILLEDARROW)
	{
		u_capSize = max((u_p0CapStyle == CAP_STYLE_ARROW || u_p0CapStyle == CAP_STYLE_FILLEDARROW) ? u_p0CapSize : 0,
						(u_p1CapStyle == CAP_STYLE_ARROW || u_p1CapStyle == CAP_STYLE_FILLEDARROW) ? u_p1CapSize : 0);
	}

	float t = (u_capSize > u_linewidth) ? (u_capSize / 2 ): (u_linewidth / 2) + ANTIALIAS;
	vec2 p = a_p0 + (a_normal.x > 0 ? 1 : 0)*l*T + a_normal.y *t* O;

	v_color = a_color;
	gl_Position = vec4(2.0*p/resolution-1.0, 0.0, 1.0);
	
	T = vec2(1, 0);
	O = vec2(0, 1);

	v_p0 = vec2(-l/2, 0);
	v_p1 = vec2(l/2, 0);
	v_p = - (v_p0 + (a_normal.x > 0 ? 1 : 0)*l*T + a_normal.y *t* O); // Dont understand why need navigate
	//v_p = (v_p0 + (a_normal.x > 0 ? 1 : 0)*l*T + a_normal.y *t* O);

	if(u_p0CapStyle == CAP_STYLE_ARROW || u_p0CapStyle == CAP_STYLE_FILLEDARROW)
	{
		startP0CapX = v_p0.x + sin(radians(60)) * u_p0CapSize;
	}
	else if(u_p0CapStyle == CAP_STYLE_ROUND)
	{
		startP0CapX = v_p0.x + u_linewidth / 2 + ANTIALIAS;
	}

	if(u_p1CapStyle == CAP_STYLE_ARROW || u_p1CapStyle == CAP_STYLE_FILLEDARROW)
	{
		startP1CapX = v_p1.x - sin(radians(60)) * u_p1CapSize;
	}
	else if(u_p1CapStyle == CAP_STYLE_ROUND)
	{
		startP1CapX = v_p1.x - (u_linewidth / 2 + ANTIALIAS);
	}
}
