#version 460 core
layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;
layout (rgba32f, binding=0 ) uniform image2D write_texture;
layout (rgba32f, binding=1 ) uniform image2D read_texture;


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

float fcwrap(float comp, float size)
{
	return mod(comp,size);
}

vec2 fwrap(vec2 coord, vec2 dims)
{
	vec2 wrapped;
	wrapped.x = fcwrap(coord.x, dims.x);
	wrapped.y = fcwrap(coord.y, dims.y);
	return wrapped;
}


void main()
{
	ivec2 uv = ivec2(gl_GlobalInvocationID.xy);
	ivec2 size = imageSize(write_texture);

	ivec2 s_lt = uv; // left and top
	ivec2 s_r = wrap(uv + ivec2(1,0), size);
	ivec2 s_b = wrap(uv + ivec2(0,1), size);
	ivec2 s_l = wrap(uv + ivec2(-1,0), size);
	ivec2 s_t = wrap(uv + ivec2(0, -1), size);
	ivec2 s_tr = wrap(uv + ivec2(1,-1), size);
	ivec2 s_br = wrap(uv + ivec2(-1,1), size);

	vec4 data = imageLoad(read_texture, uv);
	vec4 bdata = imageLoad(read_texture, s_b);
	vec4 rdata = imageLoad(read_texture, s_r);
	vec4 tdata = imageLoad(read_texture, s_t);
	vec4 ldata = imageLoad(read_texture, s_l);
	vec4 tldata = imageLoad(read_texture, s_tr);
	vec4 brdata = imageLoad(read_texture, s_br);

	float u_avg_for_v = data.x + tdata.x + rdata.x + tldata.x;
	float v_avg_for_u = data.y + bdata.y + ldata.y + brdata.y;
	float u_avg = 



}