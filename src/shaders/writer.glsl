#version 460 core

layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

layout (r32f, binding = 0) uniform image2D urt;
layout (r32f, binding = 1) uniform image2D uwt;

layout (r32f, binding = 2) uniform image2D vrt;
layout (r32f, binding = 3) uniform image2D vwt;

layout (rgba32f, binding = 4) uniform image2D srt;
layout (rgba32f, binding = 5) uniform image2D swt;



uniform vec2 position;
uniform bool writing;

void main()
{
	ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
	if (writing && distance(pos, position) < 5)
	{
		imageStore(uwt, ivec2(pos), vec4(0));	
	
		imageStore(vwt, ivec2(pos), vec4(0));
	
		imageStore(swt, ivec2(pos), vec4(0,0,0,1));
	}
}