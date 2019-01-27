#version 330 core

in vec2 a_texcoord0;
in vec4 a_texcoord1;
in vec3 a_texcoord2;
//in vec4 a_color0;

#define ANTIALIAS			1
#define a_previous			a_texcoord0
#define a_current			a_texcoord1
#define a_pointLength		a_texcoord2.x
#define a_next				(a_texcoord2.yz)

uniform float u_lineWidth;
uniform vec2 u_resolution;
uniform float u_lineLength;

out vec2 v_uv;
out vec2 v_miterDistance;

float line_distance(vec2 p, vec2 p1, vec2 p2) {
    vec2 center = (p1 + p2) * 0.5;
    float len = length(p2 - p1);
    vec2 dir = (p2 - p1) / len;
    vec2 rel_p = p - center;
    return dot(rel_p, vec2(dir.y, -dir.x));
}

void main()
{
	float w = ((u_lineWidth / 2) + ANTIALIAS);
	vec2 p;
	if(a_previous.xy == a_current.xy)	// Start line
	{
		vec2 T0 = normalize(a_next.xy - a_current.xy);
		vec2 N0 = vec2(-T0.y, T0.x);
		p = a_current.xy + a_current.z * w * N0;
		v_uv = vec2(0, w * a_current.z);
	}
	else if(a_current.xy == a_next.xy)	// End line
	{
		vec2 T1 = normalize(a_next.xy - a_previous.xy);
		vec2 N1 = vec2(-T1.y, T1.x);
		p = a_current.xy + a_current.z * w * N1;
		v_uv = vec2(u_lineLength, a_current.z * w);
	}
	else	// Body
	{
		vec2 a_previousT0 = normalize(a_current.xy - a_previous.xy);
		vec2 a_previousN0 = vec2(-a_previousT0.y, a_previousT0.x);

		vec2 a_nextT0 = normalize(a_next.xy - a_current.xy);
		vec2 a_nextN0 = vec2(-a_nextT0.y, a_nextT0.x);

		vec2 miter = normalize(a_previousN0 + a_nextN0);
		float dy = w / dot(miter, a_nextN0);
		float dx = dy / dot(miter, a_previousT0);
		
		float angle = atan(a_nextT0.y, a_nextT0.x);

		p = a_current.xy + dy * miter * ((angle < 0) ? 1 : -1);
		v_uv = vec2(a_pointLength + a_current.z * a_current.w * dx/2, a_current.z * w);
		if(a_current.z == ((angle < 0) ? -1.0 : 1.0))
		{
			p += ((angle < 0) ? 1 : -1) * dx * ((a_current.w == 1.0) ? a_nextT0 : (-a_previousT0));
		}

		//v_miterDistance.x = line_distance(a_previous, )
	}

	gl_Position = vec4(2 * p / u_resolution - 1.0, 0.0, 1.0);
}