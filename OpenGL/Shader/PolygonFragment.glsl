#version 330 core

vec4 stroke(float distance, float linewidth, float antialias, vec4 color)
{
    vec4 frag_color;
    float t = linewidth/2.0 - antialias;
    float signed_distance = distance;
    float border_distance = abs(signed_distance) - t;
    float alpha = border_distance/antialias;
    alpha = exp(-alpha*alpha);

    if( border_distance > (linewidth/2.0 + antialias) )
        discard;
    else if( border_distance < 0.0 )
        frag_color = color;
    else
        frag_color = vec4(color.rgb, color.a * alpha);

    return frag_color;
}

uniform float antialias;
uniform float linewidth;
uniform float miter_limit;

in float v_startLength;
in float v_length;
in vec2  v_caps;
in vec2  v_texcoord;
in vec2  v_bevel_distance;

void main()
{
	vec4  color = vec4(1.0, 0.0, 0.0, 1.0);

    float distance = v_texcoord.y;

    if(v_texcoord.x <= 4*antialias && antialias < abs(v_texcoord.y - sign(v_texcoord.y) * linewidth/2))
	{
		distance =  antialias - v_texcoord.x;
		distance = distance/antialias;
		gl_FragColor = vec4(color.xyz, exp(-distance * distance));
		return;
	}

    // Round join (instead of miter)
    if (v_texcoord.x < v_startLength)
    {
        distance = length(v_texcoord - vec2(v_startLength, 0));
    }
    else if(v_texcoord.x > v_startLength + v_length)
    {
        distance = length(v_texcoord - vec2(v_startLength + v_length, 0.0));
    }

    gl_FragColor = stroke(distance, linewidth, antialias, color);
}