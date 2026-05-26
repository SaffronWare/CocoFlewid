#version 460 core
out vec4 FragColor;
in vec2 coord;

uniform sampler2D UData;
uniform sampler2D VData;
uniform sampler2D SData;
void main()
{
	float u = texture(UData, coord).x;
	float v = texture(VData, coord).x;
	float density = texture(SData,coord).x;
	float solidity = texture(SData, coord).w;

	if (solidity < 1.0f)
	{
		FragColor = vec4(density);
		FragColor.w = 1.0f;
	}
	else 
	{
		FragColor = vec4(1,1,1,1);
	}
	//FragColor =vec4(data.xyw,1) ;
};