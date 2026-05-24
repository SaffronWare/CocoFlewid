#version 460 core
layout(local_size_x = 16, local_size_y = 16) in;

layout(rgba32f, binding = 0) uniform image2D FluidData;



uniform float grid_size;




void main() {

    ivec2 texelCoord = ivec2(gl_GlobalInvocationID.xy);
    ivec2 size = ivec2(imageSize(FluidData));

    ivec2 rc = ivec2(mod(texelCoord.x + 1 + size.x, size.x) , texelCoord.y);
    ivec2 uc = ivec2(texelCoord.x, mod(texelCoord.y + 1 + size.y, size.y));
    
    vec4 color = imageLoad(FluidData, texelCoord);
    vec4 right = imageLoad(FluidData, texelCoord +rc);
    vec4 up = imageLoad(FluidData, texelCoord + uc); 
    
    float divergence;

    float ux = color.z;
    float uy = color.w;
    float vx = right.z;
    float vy = up.w;

    divergence = (vx - ux + vy - uy) * 0.25f / grid_size;
    ux += divergence;
    vx -= divergence;
    uy += divergence;
    vy -= divergence;

    color.z = ux;
    color.w = uy;
    right.z = vx;
    up.w = vy;

    imageStore(FluidData, texelCoord, color);
    imageStore(FluidData, texelCoord + rc, right);
    imageStore(FluidData, texelCoord + uc, up);

}


