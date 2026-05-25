#version 460 core
layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;
layout (rgba32f, binding=0 ) uniform image2D write_texture;
layout (rgba32f, binding=1 ) uniform image2D read_texture;
uniform float grid_spacing;


int cwrap(float comp, int size)
{
	return int(floor(mod(comp, size)));
}

ivec2 wrap(vec2 coord, ivec2 dims)
{
	ivec2 wrapped;
	wrapped.x = cwrap(coord.x, dims.x);
	wrapped.y = cwrap(coord.y, dims.y);
	return wrapped;
}

void main()
{
	ivec2 uv = ivec2(gl_GlobalInvocationID.xy);
	ivec2 size = imageSize(write_texture);

	ivec2 s_lt = uv; // left and top
	ivec2 s_r = wrap(uv + ivec2(1,0), size);
	ivec2 s_b = wrap(uv + ivec2(0,1), size);

	vec4 data = imageLoad(read_texture, uv);
	float u_i = data.x;
	float v_i = data.y;
	float u_j = imageLoad(read_texture, s_r).x;
	float v_j = imageLoad(read_texture, s_b).y;

	float divergence = (v_j - v_i + u_j - u_i) / grid_spacing;


	imageStore(write_texture, uv, data);



}