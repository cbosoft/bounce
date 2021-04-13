#version 330 core

in vec4 rgba;
in vec2 TexCoords;
in vec2 centre_screen_pos;

uniform sampler2D screenTexture;

out vec4 color;

void main()
{
    vec4 sampled = texture(screenTexture, TexCoords);
    color = vec4(rgba.xyz, sampled.x+sampled.y+sampled.z);
}
