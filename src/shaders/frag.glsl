#version 460 core
out vec4 FragColor;
in vec2 coord;

uniform sampler2D FluidData;
void main()
{
	FragColor = vec4(texture(FluidData, coord).z,0,0,1);
};