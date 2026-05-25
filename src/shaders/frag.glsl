#version 460 core
out vec4 FragColor;
in vec2 coord;

uniform sampler2D FluidData;
void main()
{
	vec4 data= texture(FluidData, coord);
	if (data.w < 1)
	{
		FragColor = vec4(data.z);
		FragColor.w = 1.0f;
	}
	else 
	{
		FragColor = vec4(0,0,1,0);
	}
	FragColor =vec4(data.xyw,1) ;
};