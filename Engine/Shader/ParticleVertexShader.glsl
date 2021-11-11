#version 450 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 vel;
layout (location = 2) in vec4 colour;

out vec3 Colour;

uniform mat4 view;
uniform mat4 projection;
uniform vec3 colour;
uniform float totalTime;

void main()
{
	vec4 newPos = pos + vel * totalTime;
	gl_Position = projection * view * model * vec4(position, 1.0f);
	gl_PointSize = 3.0;
	Colour = colour; 
}