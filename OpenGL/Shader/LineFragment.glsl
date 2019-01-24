#version 330 core

uniform float u_linewidth;
uniform float u_antialias;

in vec2 v_p0, v_p1, v_p;

float getAlpha(float d, float antialias)
{
	return 1.0 - smoothstep(0.0, antialias, abs(d));
}

void main()
{
	vec2 p0Center = v_p0 + vec2(u_linewidth / 2 + u_antialias, 0);

	if(v_p.x < p0Center.x)
	{
		float d = length(v_p - p0Center);
		if(d < u_linewidth / 2) gl_FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
		else if(d < (u_linewidth / 2 + u_antialias))
		{
			float alpha = 1 - smoothstep(u_linewidth / 2, u_linewidth / 2 + u_antialias, d);
			gl_FragColor = vec4(0.0f, 0.0f, 1.0f, alpha);
		}
		else discard;
	}
	else
	{
		float d = abs(v_p.y);
		float alpha = 1 - smoothstep(u_linewidth/2, u_linewidth / 2 + u_antialias, d);
		gl_FragColor = vec4(0.0, 0.0, 1.0f, alpha);
	}
}
