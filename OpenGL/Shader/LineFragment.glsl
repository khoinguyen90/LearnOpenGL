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

uniform mat3 u_Params;

#define u_lineStyle			u_Params[0].x
#define u_linewidth			u_Params[0].y
#define u_p0CapStyle		u_Params[0].z
#define u_p0CapSize			u_Params[1].x
#define u_p1CapStyle		u_Params[1].y
#define u_p1CapSize			u_Params[1].z

in vec2 v_texcoord0, v_texcoord1, v_texcoord2;
in vec4 v_color0;
in vec3 v_texcoord3;

#define v_p0				v_texcoord0
#define v_p1				v_texcoord1
#define v_p					v_texcoord2
#define v_antialias			v_texcoord3.x
#define startP0CapX			v_texcoord3.y
#define startP1CapX			v_texcoord3.z

float line_distance(vec2 p, vec2 p1, vec2 p2) {
    vec2 center = (p1 + p2) * 0.5;
    float len = length(p2 - p1);
    vec2 dir = (p2 - p1) / len;
    vec2 rel_p = p - center;
    return dot(rel_p, vec2(dir.y, -dir.x));
}

void DrawNormalLine(float startX)
{
	switch(int(u_lineStyle))
	{
	case LINE_STYLE_FLAT:
		float d = abs(v_p.y);
		float alpha = 1 - smoothstep(u_linewidth/2, u_linewidth / 2 + v_antialias, d);
		gl_FragColor = vec4(v_color0.xyz, alpha);
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
			gl_FragColor = vec4(v_color0.xyz, alpha);
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
			gl_FragColor = vec4(v_color0.xyz, alpha);
		}
		else
		{
			gl_FragColor = v_color0;
		}
	}
	else discard;
}

void DrawRoundCap(float _startP0CapX)
{
	float d = length(v_p - vec2(_startP0CapX, 0));
	if(d < u_linewidth / 2) gl_FragColor = v_color0;
	else if(d < (u_linewidth / 2 + v_antialias))
	{
		float alpha = 1 - smoothstep(u_linewidth / 2, u_linewidth / 2 + v_antialias, d);
		gl_FragColor = vec4(v_color0.xyz, alpha);
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
