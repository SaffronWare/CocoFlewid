#version 460 core
layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;
layout (rgba32f, binding=0 ) uniform image2D write_texture;
layout (rgba32f, binding=1 ) uniform image2D read_texture;

uniform float grid_spacing;
uniform float dt;


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

vec4 read(ivec2 inp)
{
	return imageLoad(read_texture, wrap(inp, imageSize(read_texture)));
}

vec4 interpolate(vec2 value, vec2 closest)
{
		
		float offx1 = abs(value.x - closest.x);
		float offx2 = 1-offx1;
		float offy1 = abs(value.y - closest.y);
		float offy2 = 1-offy1;

		int x_off = 1;
		int y_off = 1;
		if (value.x - closest.x < 0)
		{
			x_off = -1;
		}
		if (value.y - closest.y < 0)
		{
			y_off = -1;
		}
		
		vec4 out_value=offx2 * offy2 * read(ivec2(closest));
		out_value += offx1 * offy2 * read(ivec2(closest + vec2(x_off, 0)));
		out_value += offx2 * offy1 * read(ivec2(closest + vec2(0, y_off)));
		out_value += offx1 * offy1 * read(ivec2(closest + vec2(x_off,y_off)));
		return out_value;
}


void main()
{

	ivec2 uv = ivec2(gl_GlobalInvocationID.xy);
	ivec2 size = imageSize(write_texture);

	if (uv.x < size.x && uv.y < size.y)
	{
		imageStore(write_texture, uv, imageLoad(read_texture,uv));
	}

	if (uv.x < size.x  && uv.y < size.y)
	{
		ivec2 s_r = wrap(uv + ivec2(1,0), size);
		ivec2 s_b = wrap(uv + ivec2(0,1), size);
		ivec2 s_l = wrap(uv + ivec2(-1,0), size);
		ivec2 s_t = wrap(uv + ivec2(0, -1), size);
		ivec2 s_tr = wrap(uv + ivec2(1,-1), size);
		ivec2 s_bl = wrap(uv + ivec2(-1,1), size);

		vec4 data = imageLoad(read_texture, uv);
		vec4 bdata = imageLoad(read_texture, s_b);
		vec4 rdata = imageLoad(read_texture, s_r);
		vec4 tdata = imageLoad(read_texture, s_t);
		vec4 ldata = imageLoad(read_texture, s_l);
		vec4 trdata = imageLoad(read_texture, s_tr);
		vec4 bldata = imageLoad(read_texture, s_bl);

		float u_avg_for_v = 0.25f * (data.x + tdata.x + rdata.x + trdata.x);
		float v_avg_for_u = 0.25f * (data.y + bdata.y + ldata.y + bldata.y);
		float u_avg = 0.5f * (data.x + rdata.x);
		float v_avg = 0.5f * (data.y + bdata.y);

		vec2 old_v_source = fwrap(uv -  vec2(u_avg_for_v, data.y) * dt /grid_spacing, size);
		vec2 old_u_source = fwrap(uv - vec2(data.x, v_avg_for_u) * dt / grid_spacing,size);
		vec2 old_source = fwrap(uv - vec2(u_avg, v_avg) * dt / grid_spacing, size);

		vec2 vsource = (round(old_v_source));
		vec2 usource = (round(old_u_source));
		vec2 osource = round(old_source);


		if (read(ivec2(vsource)).w < 1)
		{
		data.y = interpolate(old_v_source, vsource).y;
		}
		if (read(ivec2(usource)).w < 1)
		{
		data.x = interpolate(old_u_source, usource).x;
		}
		if (read(ivec2(osource)).w < 1)
		{
		data.z = interpolate(old_source, osource).z;
		}//probably density


		imageStore(write_texture, uv, data);
	}
	imageStore(write_texture, uv, data);
}