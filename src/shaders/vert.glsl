#version 460 core
layout (location = 0) in vec3 aPos;
out vec2 coord;

uniform float AspectRatio;


void main()
{
	gl_Position = vec4(aPos.x / AspectRatio, aPos.y, 0.0, 1.0);
	coord = (gl_Position.xy + vec2(1.0f,1.0f)) / 2.0f; 
};