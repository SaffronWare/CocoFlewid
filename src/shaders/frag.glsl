#version 460 core
out vec4 FragColor;
in vec2 coord;

uniform sampler2D UData;
uniform sampler2D VData;
uniform sampler2D SData;


float spclamp(float v)
{
	return max(0, v);
}

vec4 colorfr(float density, float speed)
{
	float s = density;

	// if fast -> go white 
	// if slow -> go blue 

	// multiply first two by smt that goes to 0 the slower it is
	float u = 1.3f - exp(-5*speed);

	return vec4(0.8f*s*u,s*u,s,1.0f);

}

void main()
{
	float u = texture(UData, coord).x;
	float v = texture(VData, coord).x;
	float density = texture(SData,coord).x;
	float solidity = texture(SData, coord).w;
	float pressure = texture(SData, coord).y;

	if (solidity < 1.0f)
	{
		FragColor = colorfr(density, u);
	}
	else 
	{
		FragColor = vec4(1,1,1,1);
	}
	//FragColor =vec4(data.xyw,1) ;
};