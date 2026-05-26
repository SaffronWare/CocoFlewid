#version 460 core
layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;
layout (r32f, binding=0 ) uniform image2D urt;
layout (r32f, binding=1 ) uniform image2D uwt;
layout (r32f, binding=2) uniform image2D vrt;
layout (r32f, binding=3) uniform image2D vwt;
layout (rgba32f, binding=4) uniform image2D srt;
layout (rgba32f, binding=5) uniform image2D swt;

void main()
{
	ivec2 uv = ivec2(gl_GlobalInvocationID.xy);
	ivec2 size = imageSize(srt);


	if (uv.x < size.x  && uv.y < size.y)
	{
		imageStore(uwt, uv,imageLoad(urt, uv));
		imageStore(vwt, uv,imageLoad(vrt, uv));
		imageStore(swt, uv,imageLoad(srt, uv));
	}
}