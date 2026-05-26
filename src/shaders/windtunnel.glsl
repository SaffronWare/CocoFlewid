#version 460 core

layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

layout (r32f, binding = 0) uniform image2D urt;
layout (r32f, binding = 1) uniform image2D uwt;

layout (r32f, binding = 2) uniform image2D vrt;
layout (r32f, binding = 3) uniform image2D vwt;

layout (rgba32f, binding = 4) uniform image2D srt;
layout (rgba32f, binding = 5) uniform image2D swt;

void main()
{
    ivec2 uv = ivec2(gl_GlobalInvocationID.xy);
    ivec2 size = imageSize(swt);

    if (uv.x >= size.x || uv.y >= size.y)
        return;

    float density = 0;
    
    if (float(uv.x) / float(size.x) < 0.05f)
    {
        
        if (mod(float(uv.y) / float(size.y), 0.1) < 0.005f)
        {
        density = 1.0;
        }
        imageStore(swt, uv, vec4(density, 0.0, 0.0, 0.0));
        imageStore(uwt, uv, vec4(1.0,0.0,0.0,0.0));
        imageStore(vwt, uv, vec4(0.0f));
    }



    
}