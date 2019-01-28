#version 330 core

#define ANTIALIAS		1

uniform float u_lineWidth;
uniform vec2 u_resolution;
uniform float u_lineLength;
in vec2 v_uv;
in vec2 v_miterDistance;

void main()
{
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1);
	//return;
	
	if(v_miterDistance.x < ANTIALIAS)
	{
		gl_FragColor = vec4(0.0, 0.0, 1.0, 1);
		return;
	}

	float w = u_lineWidth / 2 - ANTIALIAS;
	float d = 0;
	
	//if(int(v_uv.x) % (int(u_lineWidth) * 6 * 2) < u_lineWidth * 6)
	{
		d = abs(v_uv.y) - w;
		if(d < 0)
		{
			gl_FragColor = vec4(1.0, 0.0, 0.0, 1);
		}
		else
		{
			d = d/ANTIALIAS;
			gl_FragColor = vec4(1.0, 0.0, 0.0, exp(-d * d));
		}
	}
	//else
	{
		//discard;
	}
}