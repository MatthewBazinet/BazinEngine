#version 450 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 vel;
layout (location = 2) in vec4 colour;

out vec4 Colour;

uniform mat4 view;
uniform mat4 projection;
uniform float totalTime;

void main()
{
	Colour = colour; 
	vec4 newPos = vec4(pos + (vel * totalTime),1.0);
	gl_Position = projection * view * newPos;
	gl_PointSize = 3.0;
	
}