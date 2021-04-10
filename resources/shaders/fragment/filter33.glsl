#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D screenTexture;
uniform vec3 kernel_a;
uniform vec3 kernel_b;
uniform vec3 kernel_c;
uniform float kernel_norm;

const float offset = 1.0 / 400.0;
const vec2 offsets[9] = vec2[](
    vec2(-offset,  offset), // top-left
    vec2( 0.0f,    offset), // top-center
    vec2( offset,  offset), // top-right
    vec2(-offset,  0.0f),   // center-left
    vec2( 0.0f,    0.0f),   // center-center
    vec2( offset,  0.0f),   // center-right
    vec2(-offset, -offset), // bottom-left
    vec2( 0.0f,   -offset), // bottom-center
    vec2( offset, -offset)  // bottom-right
);

void main()
{
    float kernel[9] = float[](
        kernel_a.x, kernel_a.y, kernel_a.z,
        kernel_b.x, kernel_b.y, kernel_b.z,
        kernel_c.x, kernel_c.y, kernel_c.z
    );
    vec3 pcolor = vec3(texture(screenTexture, TexCoords));
    vec3 col = vec3(0.0f);
    for (int i = 0; i < 9; i++){
        vec3 sampled = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
        col += sampled*kernel[i]*kernel_norm;
    }
    color = vec4(col, 1.0);
}
