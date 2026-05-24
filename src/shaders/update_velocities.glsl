#version 460 core
layout(local_size_x = 16, local_size_y = 16) in;
layout(rgba32f, binding = 0) uniform image2D FluidData;
layout(rgba32f, binding=1) uniform image2D DensityData;





void main() {
    ivec2 texelCoord = ivec2(gl_GlobalInvocationID.xy);
    ivec2 center = imageSize(FluidData) / 2;
    
    
   
    vec4 currf = imageLoad(FluidData, texelCoord);
    currf.zw = currf.xy;
    imageStore(FluidData, texelCoord, currf);

    vec4 currd = imageLoad(DensityData, texelCoord);
    currd.y = currd.x;
    imageStore(DensityData, texelCoord, currd);
    

    if (distance(texelCoord, center) < 8)
    {
        imageStore(DensityData, texelCoord, vec4(0.0f,10.0f,0.0f, 0.0f));
        imageStore(FluidData, texelCoord, vec4(0.0f, 0.0f, 0.0f, 1.0f));
    }

  
}


