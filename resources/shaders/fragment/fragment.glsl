#version 330 core

in vec4 rgba;
in vec2 TexCoords;
in vec2 centre_screen_pos;

out vec4 color;

void main()
{
    color = rgba;
}
