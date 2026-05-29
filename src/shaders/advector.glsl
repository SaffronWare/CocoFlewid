#version 460 core
layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;
layout (r32f, binding=0 ) uniform image2D urt;
layout (r32f, binding=1 ) uniform image2D uwt;
layout (r32f, binding=2) uniform image2D vrt;
layout (r32f, binding=3) uniform image2D vwt;
layout (rgba32f, binding=4) uniform image2D srt;
layout (rgba32f, binding=5) uniform image2D swt;


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

float ru(vec2 uv_)
{
	uv_ = fwrap(uv_, imageSize(urt));
	return imageLoad(urt, ivec2(uv_)).x;
}
float rv(vec2 uv_)
{
	uv_ = fwrap(uv_, imageSize(vrt));
	return imageLoad(vrt, ivec2(uv_)).x;
}

float rdens(vec2 uv_)
{
	uv_ = fwrap(uv_, imageSize(srt));
	return imageLoad(srt, ivec2(uv_)).x;
}
float solidity(vec2 uv_)
{
	return imageLoad(srt, ivec2(uv_)).w;
};

void set_u(vec2 uv, float u_v)
{
	uv = fwrap(uv, imageSize(urt));
	vec4 d = imageLoad(urt, ivec2(uv));
	d.x = u_v;
	imageStore(uwt, ivec2(uv), d);
}

void set_v(vec2 uv, float v_v)
{
	uv = fwrap(uv, imageSize(vrt));
	vec4 d = imageLoad(vrt, ivec2(uv));
	d.x = v_v;
	imageStore(vwt, ivec2(uv), d);
}

void set_density(vec2 uv, float d)
{
	uv = fwrap(uv, imageSize(srt));
	vec4 data = imageLoad(srt, ivec2(uv));
	data.x = d;
	imageStore(swt, ivec2(uv), data);
}



float interpolateu(vec2 value, vec2 closest)
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
		
		float out_value =offx2 * offy2 * ru(closest);
		out_value += offx1 * offy2 * ru(vec2(closest + vec2(x_off, 0)));
		out_value += offx2 * offy1 * ru(vec2(closest + vec2(0, y_off)));
		out_value += offx1 * offy1 * ru(vec2(closest + vec2(x_off,y_off)));
		return out_value;
}

float interpolatev(vec2 value, vec2 closest)
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
		
		float out_value =offx2 * offy2 * rv(closest);
		out_value += offx1 * offy2 * rv(vec2(closest + vec2(x_off, 0)));
		out_value += offx2 * offy1 * rv(vec2(closest + vec2(0, y_off)));
		out_value += offx1 * offy1 * rv(vec2(closest + vec2(x_off,y_off)));
		return out_value;
}

float interpolatedensity(vec2 value, vec2 closest)
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
		
		float out_value =offx2 * offy2 * rdens(closest);
		out_value += offx1 * offy2 * rdens(vec2(closest + vec2(x_off, 0)));
		out_value += offx2 * offy1 * rdens(vec2(closest + vec2(0, y_off)));
		out_value += offx1 * offy1 * rdens(vec2(closest + vec2(x_off,y_off)));
		return out_value;
}



void main()
{

	ivec2 uv = ivec2(gl_GlobalInvocationID.xy);
	ivec2 size = imageSize(srt);


	if (uv.x < size.x  && uv.y < size.y)
	{
		ivec2 s_r = wrap(uv + ivec2(1,0), size);
		ivec2 s_b = wrap(uv + ivec2(0,1), size);
		ivec2 s_l = wrap(uv + ivec2(-1,0), size);
		ivec2 s_t = wrap(uv + ivec2(0, -1), size);
		ivec2 s_tr = wrap(uv + ivec2(1,-1), size);
		ivec2 s_bl = wrap(uv + ivec2(-1,1), size);


		float sld = solidity(uv);
		float u = ru(uv);
		float v = rv(uv);
		float top_u = ru(s_t);
		float right_u = ru(s_r);
		float top_right_u = ru(s_tr);
		float bottom_v = rv(s_b);
		float left_v = rv(s_l);
		float bottom_left_v = rv(s_bl);

		float u_avg_for_v = 0.25f * (u+top_u+right_u+top_right_u);
		float v_avg_for_u = 0.25f * (v+bottom_v + left_v + bottom_left_v);
		float u_avg = 0.5f * (u + right_u);
		float v_avg = 0.5f * (v + bottom_v);

		vec2 old_v_source = fwrap(uv -  vec2(u_avg_for_v, v) * dt /grid_spacing, size);
		vec2 old_u_source = fwrap(uv - vec2(u, v_avg_for_u) * dt / grid_spacing,size);
		vec2 old_source = fwrap(uv - vec2(u_avg, v_avg) * dt / grid_spacing, size);

		vec2 vsource = (round(old_v_source));
		vec2 usource = (round(old_u_source));
		vec2 osource = round(old_source);


		if (solidity(vsource) < 1)
		{
			set_v(uv,interpolatev(old_v_source, vsource));
		}
		else 
		{
			set_v(uv, 0);
		}
		if (solidity(usource) < 1)
		{
			set_u(uv,interpolateu(old_u_source, usource));
			
		}
		else 
		{
			set_u(uv,0);
		}
		if (solidity(osource) < 1)
		{
			set_density(uv, interpolatedensity(old_source, osource));
		}
		else {
			set_density(uv, 0);
		}

	}
}