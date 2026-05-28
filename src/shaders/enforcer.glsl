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
uniform int type;

const float overlaxation = 1.9f;

float ru(vec2 uv_)
{
	return imageLoad(urt, ivec2(uv_)).x;
}
float rv(vec2 uv_)
{
	return imageLoad(vrt, ivec2(uv_)).x;
}
float solidity(vec2 uv_)
{
	return imageLoad(srt, ivec2(uv_)).w;
};

void set_u(vec2 uv, float u_v)
{
	vec4 d = imageLoad(urt, ivec2(uv));
	d.x = u_v;
	imageStore(uwt, ivec2(uv), d);
}

void set_p(vec2 uv, float p)
{
	vec4 d = imageLoad(srt, ivec2(uv));
	d.y = p;
	imageStore(swt, ivec2(uv), d);
}

void set_v(vec2 uv, float v_v)
{
	vec4 d = imageLoad(vrt, ivec2(uv));
	d.x = v_v;
	imageStore(vwt, ivec2(uv), d);
}

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
	ivec2 size = imageSize(urt);

	if (uv.x < size.x  && uv.y < size.y && (uv.x + uv.y)%2 == type)
	{
		ivec2 s_r = wrap(uv + ivec2(1,0), size);
		ivec2 s_b = wrap(uv + ivec2(0,1), size);
		ivec2 s_l = wrap(uv + ivec2(-1,0), size);
		ivec2 s_t = wrap(uv + ivec2(0, -1), size);


		float u = ru(uv);
		float v = rv(uv);
		float u_right = ru(s_r);
		float v_bottom = rv(s_b);
		float sld = solidity(uv);
		float sld_top = solidity(s_t);
		float sld_bottom = solidity(s_b);
		float sld_right = solidity(s_r);
		float sld_left = solidity(s_l);

		if (sld != 1.0f)
		{

			float solidity = sld_top + sld_bottom + sld_right + sld_left;
			solidity = 4.0f-solidity;
			if (solidity > 0.01f)
			{

				float divergence = (v_bottom - v + u_right - u) / grid_spacing;
				float correction_factor = divergence  * overlaxation * grid_spacing;

				u += correction_factor * (1-sld_left) / solidity;
				v += correction_factor * (1-sld_top) / solidity;
				u_right -= correction_factor * (1-sld_right) / solidity;
				v_bottom -= correction_factor * (1-sld_bottom) / solidity;

				float p_change = divergence * 1.255f * grid_spacing / solidity / dt;

				set_u(uv, u);
				set_v(uv, v);
				set_u(s_r, u_right);
				set_v(s_b, v_bottom);

				set_p(uv, p_change);

				
			}
		}

		


	}

}