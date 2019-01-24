#version 330 core

float SDF_ellipse(vec2 p, vec2 ab)
{
    // The function does not like circles
    if (ab.x == ab.y) ab.x = ab.x*0.9999;

    p = abs( p ); if( p.x > p.y ){ p=p.yx; ab=ab.yx; }
    float l = ab.y*ab.y - ab.x*ab.x;
    float m = ab.x*p.x/l;
    float n = ab.y*p.y/l;
    float m2 = m*m;
    float n2 = n*n;
    float c = (m2 + n2 - 1.0)/3.0;
    float c3 = c*c*c;
    float q = c3 + m2*n2*2.0;
    float d = c3 + m2*n2;
    float g = m + m*n2;
    float co;

    if( d<0.0 ) {
        float p = acos(q/c3)/3.0;
        float s = cos(p);
        float t = sin(p)*sqrt(3.0);
        float rx = sqrt( -c*(s + t + 2.0) + m2 );
        float ry = sqrt( -c*(s - t + 2.0) + m2 );
        co = ( ry + sign(l)*rx + abs(g)/(rx*ry) - m)/2.0;
    } else {
        float h = 2.0*m*n*sqrt( d );
        float s = sign(q+h)*pow( abs(q+h), 1.0/3.0 );
        float u = sign(q-h)*pow( abs(q-h), 1.0/3.0 );
        float rx = -s - u - c*4.0 + 2.0*m2;
        float ry = (s - u)*sqrt(3.0);
        float rm = sqrt( rx*rx + ry*ry );
        float p = ry/sqrt(rm-rx);
        co = (p + 2.0*g/rm - m)/2.0;
    }
    float si = sqrt( 1.0 - co*co );
    vec2 r = vec2( ab.x*co, ab.y*si );
    return length(r - p ) * sign(p.y-r.y);
}

in vec2 v_position;
void main()
{
	float thickness = 0.05;
	float antialias = 0.005;

	vec4 fillColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	vec4 borderColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);

	float radius = 0.3;

    float d = SDF_ellipse(v_position, vec2(0.3, 0.4));

	if((d > 0 && d < thickness/2) || (d < 0 && d > -thickness/2))
	{
		gl_FragColor = borderColor;
	}
	else if(d > 0 && d < (thickness/2 + antialias))
	{
		float alpha = getAlpha(d - thickness/2, antialias);
		gl_FragColor = vec4(borderColor.xyz, alpha);
	}
	else if(d < 0 && d > -(thickness/2 + antialias))
	{
		float alpha = getAlpha(d + thickness/2, antialias);
		if(fillColor.w != 0)
		{
			gl_FragColor = vec4(mix(fillColor, borderColor, alpha).xyz, 1.0f);
		}
		else
		{
			gl_FragColor = vec4(borderColor.xyz, alpha);
		}
	}
	else if(d < 0)
	{
		gl_FragColor = fillColor;
	}
	else
	{
		discard;
	}
} 