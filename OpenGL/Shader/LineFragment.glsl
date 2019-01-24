#version 330 core

#define LINE_STYLE_FLAT				0
#define LINE_STYLE_SUNKEN			1
#define LINE_STYLE_RAISED			2
#define LINE_STYLE_DASHED			3

#define CAP_STYLE_FLAT				0
#define CAP_STYLE_ROUND				1
#define CAP_STYLE_ARROW				2
#define CAP_STYLE_FILLEDARROW		3
#define DASHED_WIDTH				6

uniform int u_linewidth;
uniform int u_lineStyle;
uniform int u_p0CapStyle;
uniform int u_p1CapStyle;
uniform int u_p0CapSize;
uniform int u_p1CapSize;

in vec2 v_p0, v_p1, v_p;
in vec4 v_color;
in float v_antialias, startP0CapX, startP1CapX;

float line_distance(vec2 p, vec2 p1, vec2 p2) {
    vec2 center = (p1 + p2) * 0.5;
    float len = length(p2 - p1);
    vec2 dir = (p2 - p1) / len;
    vec2 rel_p = p - center;
    return dot(rel_p, vec2(dir.y, -dir.x));
}

void DrawNormalLine(float startX)
{
	switch(u_lineStyle)
	{
	case LINE_STYLE_FLAT:
		float d = abs(v_p.y);
		float alpha = 1 - smoothstep(u_linewidth/2, u_linewidth / 2 + v_antialias, d);
		gl_FragColor = vec4(v_color.xyz, alpha);
		break;

	case LINE_STYLE_SUNKEN:
		break;

	case LINE_STYLE_RAISED:
		break;

	case LINE_STYLE_DASHED:
		int dashX = int(v_p.x - startX);
		if(dashX % (int(u_linewidth) * DASHED_WIDTH * 2) < u_linewidth * DASHED_WIDTH)
		{
			float d = abs(v_p.y);
			float alpha = 1 - smoothstep(u_linewidth/2, u_linewidth / 2 + v_antialias, d);
			gl_FragColor = vec4(v_color.xyz, alpha);
		}
		else
		{
			discard;
		}
		break;

	default:
		break;
	}
}

void DrawArrowCap(float startCapX, bool isP0)
{
	vec2 arrowP0 = isP0 ? v_p0 : v_p1;
	vec2 arrowP1 = vec2(startCapX , ((isP0 ? u_p0CapSize : u_p1CapSize) / 2));
	vec2 arrowP2 = vec2(arrowP1.x, -arrowP1.y);

	float d = 0;
	if(v_p.y > 0)
		d = line_distance(v_p, arrowP0, arrowP1);
	else
		d = line_distance(v_p, arrowP2, arrowP0);

	if(isP0 ? (d > 0) : (d < 0))
	{
		d = abs(d);
		if(d < v_antialias)
		{
			float alpha = smoothstep(0, v_antialias, d);
			gl_FragColor = vec4(v_color.xyz, alpha);
		}
		else
		{
			gl_FragColor = v_color;
		}
	}
	else discard;
}

void DrawRoundCap(float startP0CapX)
{
	float d = length(v_p - vec2(startP0CapX, 0));
	if(d < u_linewidth / 2) gl_FragColor = v_color;
	else if(d < (u_linewidth / 2 + v_antialias))
	{
		float alpha = 1 - smoothstep(u_linewidth / 2, u_linewidth / 2 + v_antialias, d);
		gl_FragColor = vec4(v_color.xyz, alpha);
	}
	else discard;
}


void main()
{
	if(u_p0CapStyle != CAP_STYLE_FLAT && v_p.x < startP0CapX)
	{
		if(u_p0CapStyle == CAP_STYLE_ROUND)
		{
			DrawRoundCap(startP0CapX);
		}
		else // CAP_STYLE_ARROW or CAP_STYLE_FILLEDARROW
		{
			DrawArrowCap(startP0CapX, true);
		}
	
		return;
	}
	
	if(u_p1CapStyle != CAP_STYLE_FLAT && v_p.x > startP1CapX)
	{
		if(u_p1CapStyle == CAP_STYLE_ROUND)
		{
			DrawRoundCap(startP1CapX);
		}
		else // CAP_STYLE_ARROW or CAP_STYLE_FILLEDARROW
		{
			DrawArrowCap(startP1CapX, false);
		}
	
		return;
	}

	DrawNormalLine(startP0CapX);
}
