#version 330 core

//uniform float antialias;
//in float v_alpha, v_thickness;
//in vec2 v_p0, v_p1, v_p;
//
//void main()
//{
//    float d = 0;
//    if( v_p.x < 0 )
//	{
//	    d = length(v_p - v_p0) - v_thickness/2.0 + antialias/2.0;
//	}
//    else if ( v_p.x > length(v_p1-v_p0) )
//	{
//	    d = length(v_p - v_p1) - v_thickness/2.0 + antialias/2.0;
//	}
//    else
//	{
//	    d = abs(v_p.y) - v_thickness/2.0 + antialias/2.0;
//	}
//
//    if( d < 0)
//	{
//	    gl_FragColor = vec4(0.0, 0.0, 0.0, v_alpha);
//	}
//    else if (d < antialias)
//	{
//        d = exp(-d*d);
//        gl_FragColor = vec4(0.0, 0.0, 0.0, d*v_alpha);
//    }
//	else
//	{
//		gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
//	}
//}

float distance(vec2 P, vec2 center, float radius)
{
    return length(P-center) - radius;
}

in vec2 v_position;
void main()
{
	float antialias = 4;
    const float epsilon = 10;
	float radius = 100;

    float d = distance(v_position, vec2(0.0), radius);

    if (d < -epsilon)
        gl_FragColor = vec4(1.0-abs(d), 0.0, 0.0, 1.0);
    else if (d > epsilon)
        gl_FragColor = vec4(0.0, 0.0, 1.0-abs(d), 1.0);
    else 
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
} 