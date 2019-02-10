#version 330 core

uniform float antialias;
uniform float linewidth;
uniform float miter_limit;
uniform vec2 resolution;

layout(location = 0) in vec2 p0;
layout(location = 1) in vec2 p1;
layout(location = 2) in vec2 p2;
layout(location = 3) in vec2 p3;
layout(location = 4) in vec2 a_normal;
layout(location = 5) in float a_startLength;

out float v_startLength;
out float v_length;
out vec2  v_caps;
out vec2  v_texcoord;
out vec2  v_bevel_distance;

float compute_u(vec2 p0, vec2 p1, vec2 p)
{
    vec2 v = p1 - p0;
    float l = length(v);
    return ((p.x-p0.x)*v.x + (p.y-p0.y)*v.y) / l;
}

float line_distance(vec2 p0, vec2 p1, vec2 p)
{
    // Projection p' of p such that p' = p0 + u*(p1-p0)
    vec2 v = p1 - p0;
    float l2 = v.x*v.x + v.y*v.y;
    float u = ((p.x-p0.x)*v.x + (p.y-p0.y)*v.y) / l2;

    // h is the projection of p on (p0,p1)
    vec2 h = p0 + u*v;

    return length(p-h);
}

void main()
{
	v_startLength = a_startLength;

    // Determine the direction of each of the 3 segments (previous, current, next)
    vec2 v0 = normalize(p1 - p0);
    vec2 v1 = normalize(p2 - p1);
    vec2 v2 = normalize(p3 - p2);

	// Determine the normal of each of the 3 segments (previous, current, next)
    vec2 n0 = vec2(-v0.y, v0.x);
    vec2 n1 = vec2(-v1.y, v1.x);
    vec2 n2 = vec2(-v2.y, v2.x);

	// Determine miter lines by averaging the normals of the 2 segments
    vec2 miter_a = normalize(n0 + n1); // miter at start of current segment
    vec2 miter_b = normalize(n1 + n2); // miter at end of current segment

    // Determine the length of the miter by projecting it onto normal
    vec2 p,v;
    float d;
    float w = linewidth/2.0 + antialias;
    v_length = length(p2-p1);

    float length_a = w / dot(miter_a, n1);
    float length_b = w / dot(miter_b, n1);

    float m = miter_limit*linewidth/2.0;

    // Angle between prev and current segment (sign only)
    float d0 = -sign(v0.x*v1.y - v0.y*v1.x);

    // Angle between current and next segment (sign only)
    float d1 = -sign(v1.x*v2.y - v1.y*v2.x);

	if(a_normal.x < 0) // Start point
	{
		if(p0 == p1) // start cap
		{
			p = p1 + a_normal.y * w * n1;
			v_texcoord = vec2(a_startLength, a_normal.y * w);
		}
		else
		{
			float dx = abs(2 * w / dot(v0, n1));
			p = p1 + a_normal.y * miter_a * length_a;
			v_texcoord = vec2(a_startLength + compute_u(p1, p2, p), a_normal.y * w);

			// Improve later
			p -= (d0 * a_normal.y == -1) ? dx * v1 : vec2(0, 0);
			v_texcoord.x -= (d0 * a_normal.y == -1) ? dx : 0;
		}

		if( p2 == p3 ) v_caps.y = v_texcoord.x;
		else           v_caps.y = 1.0;
	}
	else // End point
	{
		if(p2 == p3) // end cap
		{
			p = p2 + a_normal.y * w * n1;
			v_texcoord = vec2(a_startLength + v_length, a_normal.y * w);
		}
		else
		{
			float dx = abs(2 * w / dot(v1, n2));
			p = p2 + a_normal.y * miter_b * length_b;
			v_texcoord = vec2(a_startLength + compute_u(p1, p2, p), a_normal.y * w);

			// Improve later
			p += (d1 * a_normal.y == -1) ? dx * v1 : vec2(0, 0);
			v_texcoord.x += (d1 * a_normal.y == -1) ? dx : 0;
		}

		if( p0 == p1 ) v_caps.x = v_texcoord.x;
		else           v_caps.x = 1.0;
	}

	gl_Position = vec4(2*p/resolution - 1, 0.0, 1.0);
}