#version 460 core
out vec4 FragColor;
in vec2 coord;

uniform sampler2D FluidData;
uniform sampler2D DensityData;

void main()
{
	
	FragColor = vec4(texture(DensityData, coord).y);
	FragColor = vec4(0, 0, texture(FluidData, coord).w,1);
	FragColor.w = 1.0f;
	//FragColor = vec4(coord, 0, 1);
};