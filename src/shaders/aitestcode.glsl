#version 460 core

layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

layout (rgba32f, binding = 0) uniform image2D write_texture;
layout (rgba32f, binding = 1) uniform image2D read_texture;

void main()
{
    ivec2 uv = ivec2(gl_GlobalInvocationID.xy);
    ivec2 size = imageSize(write_texture);

    if (uv.x >= size.x || uv.y >= size.y)
        return;

    vec2 dims = vec2(size);

    vec2 p = (vec2(uv) + vec2(0.5)) / dims;

    vec2 center = vec2(0.35, 0.5);
    float radius = 0.08;

    float d = length(p - center);

    vec4 data = vec4(0.0);

    // Velocity everywhere
    data.x = 0.15; // u velocity, rightward
    data.y = 0.0;  // v velocity

    // Density only inside circle
    if (d < radius)
    {
        data.z = 1.0;
    }

    imageStore(write_texture, uv, data);
}