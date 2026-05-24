#version 460 core
out vec4 FragColor;
in vec2 coord;

uniform sampler2D FluidData;

void main()
{
	
	FragColor = vec4(texture(FluidData, coord).xyz,1);
	//FragColor = vec4(coord, 0, 1);
};