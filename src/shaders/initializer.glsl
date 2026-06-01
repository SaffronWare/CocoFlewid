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

    vec2 dims = vec2(size);

    vec2 p = (vec2(uv) + vec2(0.5)) / dims;


    ivec2 obstacleCenter = size / 2 -ivec2(30,0);
    float obstacleRadius = 20.0;
    float obstacleD = distance(vec2(uv), vec2(obstacleCenter));

    float density = 0.0;
    float solidity = 0.0;

    float u = 0.0f;
    float v = 0.0;

    if (obstacleD < obstacleRadius)
    {
        solidity = 0.0;
        density = 0.0;


        u = 0.0;
        v = 0.0;
    }

    imageStore(uwt, uv, vec4(u, 0.0, 0.0, 0.0));
    imageStore(vwt, uv, vec4(v, 0.0, 0.0, 0.0));

    imageStore(swt, uv, vec4(density, 0.0, 0.0, solidity));
}