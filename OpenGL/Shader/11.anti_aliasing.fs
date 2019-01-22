#version 330 core

float distance(vec2 P, vec2 center, float radius)
{
    return length(P-center) - radius;
}

in vec2 v_position;
void main()
{
	float antialias = 0.005;
    const float epsilon = 0.01;
	float radius = 0.3;

    float d = distance(v_position, vec2(0.0), radius);

    if (d < -epsilon)
        gl_FragColor = vec4(1.0-abs(d), 0.0, 0.0, 1.0);
    else if (d > epsilon)
        gl_FragColor = vec4(0.0, 0.0, 1.0-abs(d), 1.0);
    else 
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}  