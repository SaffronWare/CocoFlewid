#version 460 core
layout(local_size_x = 16, local_size_y = 16) in;

layout(rgba32f, binding = 0) uniform image2D FluidData;

uniform float dt;
#version 460 core
layout(local_size_x = 16, local_size_y = 16) in;

uniform float grid_size;

uniform float dt;

layout (rgba32f, binding=0) uniform Image2D FluidData;


void main() {

    ivec2 texelCoord = ivec2(gl_GlobalInvocationID.xy);
    ivec2 size = ivec2(imageSize(FluidData));

    ivec2 rc = ivec2(mod(texelCoord.x + 1 + size.x, size.x) , texelCoord.y);
    ivec2 uc = ivec2(texelCoord.x, mod(texelCoord.y + 1 + size.y, size.y));
    
    vec4 color = imageLoad(FluidData, texelCoord);
    vec4 right = imageLoad(FluidData, texelCoord +rc);
    vec4 up = imageLoad(FluidData, texelCoord + uc); 

    float u = (color.x + right.x ) / 2.0f;
    float v = (color.y + right.y) / 2.0f;
    
    
}


