#version 460 core
layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;
layout (r32f, binding=0 ) uniform image2D urt;
layout (r32f, binding=1 ) uniform image2D uwt;
layout (r32f, binding=2) uniform image2D vrt;
layout (r32f, binding=3) uniform image2D vwt;
layout (rgba32f, binding=4) uniform image2D srt;
layout (rgba32f, binding=5) uniform image2D swt;
uniform float grid_spacing;
uniform int type;

const float overlaxation = 1.9f;

float u(vec2 uv_)
{
	return imageLoad(urt, ivec2(uv_)).r;
}
float v(vec2 uv_)
{
	return imageLoad(vrt, ivec2(uv_)).r;
}
float solidity(vec2 uv_)
{
	return imageLoad(srt, ivec2(uv_)).w;
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

	if (uv.x < size.x && uv.y < size.y)
	{
		imageStore(uwt, uv, imageLoad(urt,uv));
		imageStore(vwt, uv, imageLoad(vrt,uv));
		imageStore(swt, uv, imageLoad(srt,uv));
	}

	if (uv.x < size.x  && uv.y < size.y && (uv.x + uv.y)%2 == type)
	{
		ivec2 s_r = wrap(uv + ivec2(1,0), size);
		ivec2 s_b = wrap(uv + ivec2(0,1), size);
		ivec2 s_l = wrap(uv + ivec2(-1,0), size);
		ivec2 s_t = wrap(uv + ivec2(0, -1), size);


		vec4 data = imageLoad(srt, uv);
		vec4 data_u= imageLoad(urt, uv);
		vec4 data_v = imageLoad(vrt, uv);
		vec4 bdata = imageLoad(vrt, s_b);
		vec4 rdata = imageLoad(urt, s_r);
		vec4 tdata = imageLoad(vrt, s_t);
		vec4 ldata = imageLoad(urt, s_l);

		if (data.w != 1.0f)
		{

			float solidity = bdata.w + rdata.w + tdata.w + ldata.w;
			solidity = 4.0f-solidity;
			if (solidity > 0.01f)
			{

				float u_i = data.x;
				float v_i = data.y;
				float u_j = rdata.x;
				float v_j = bdata.y;

				float divergence = (v_j - v_i + u_j - u_i) / grid_spacing;
				float correction_factor = divergence  * overlaxation * grid_spacing;

				data.x += correction_factor * (1-ldata.w) / solidity;
				data.y += correction_factor * (1-tdata.w) / solidity;
				rdata.x -= correction_factor * (1-rdata.w) / solidity;
				bdata.y -= correction_factor * (1-bdata.w) / solidity;

				imageStore(write_texture, uv, data);
				//imageStore(write_texture, s_r, rdata);
				//imageStore(write_texture, s_b, bdata);
				
			}
		}

		


	}

}