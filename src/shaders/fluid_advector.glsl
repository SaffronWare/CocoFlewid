#version 460 core
layout(local_size_x = 16, local_size_y = 16) in;
layout(rgba32f, binding = 0) uniform image2D FluidData;
layout(rgba32f, binding=1) uniform image2D DensityData;
uniform float dt;
uniform float grid_size;




void main() {

    ivec2 texelCoord = ivec2(gl_GlobalInvocationID.xy);
    ivec2 size = ivec2(imageSize(FluidData));

    ivec2 rc = ivec2(mod(texelCoord.x + 1 + size.x, size.x) , texelCoord.y);
    ivec2 uc = ivec2(texelCoord.x, mod(texelCoord.y + 1 + size.y, size.y));
    
    vec4 color = imageLoad(FluidData, texelCoord);
    vec4 right = imageLoad(FluidData, rc);
    vec4 up = imageLoad(FluidData, uc); 

    float u = (color.z + right.w ) / 2.0f;
    float v = (color.z + up.w) / 2.0f;

    int prev_x = texelCoord.x - int(floor(u * dt / grid_size));
    int prev_y = texelCoord.y - int(floor(v * dt / grid_size));
    ivec2 prevc= ivec2(prev_x, prev_y);
   
    vec4 prev = imageLoad(FluidData, prevc);
    color.xy = prev.zw;

    vec4 prev_density = imageLoad(DensityData, prevc);
    vec4 curr_density=  imageLoad(DensityData, texelCoord);
    curr_density.x = prev_density.y;

    imageStore(FluidData, texelCoord, color); 
    imageStore(DensityData, texelCoord, curr_density);

  
}


