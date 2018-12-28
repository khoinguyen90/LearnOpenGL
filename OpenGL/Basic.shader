#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 vertexInputColor;
layout(location = 2) in vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 vertexOutputColor;
out vec2 v_TextCoord;

uniform mat4 transform;

void main()
{
	v_TextCoord = texCoord;
	vertexOutputColor = vertexInputColor;
	gl_Position = projection * view * model * position;
};

#shader fragment
#version 330 core

in vec3 vertexOutputColor;
layout(location = 0) out vec4 FragColor;
//uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform sampler2D u_OtherTexture;
in vec2 v_TextCoord;

void main()
{
	FragColor = mix(texture(u_Texture, v_TextCoord), texture(u_OtherTexture, v_TextCoord), 0.2f);
};