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

float SDF_fake_box(vec2 p, vec2 size)
{
    return max(abs(p.x)-size.x, abs(p.y)-size.y);
}

void main()
{
	vec4  color = vec4(1.0, 0.0, 0.0, 1.0);
	//gl_FragColor = color; return;

	float phase = -linewidth * 3;
	float spacing = 12;
    float center = v_texcoord.x + spacing/2.0*linewidth
                 - mod(v_texcoord.x + phase + spacing/2.0*linewidth, spacing*linewidth);

	vec2 size = vec2(3 * linewidth - antialias, linewidth/2);
	float d = SDF_fake_box(v_texcoord - vec2(center, 0), size);

	float distance = v_texcoord.y;
	
	if(abs(v_texcoord.x - center) >= 3 *linewidth)
	{
		discard;
	}

	if(d <= antialias)
	{
		distance = d + linewidth/2;
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