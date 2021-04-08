#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colour;

out vec3 rgb;

void main() {
  gl_Position = vec4(pos, 1.0f);
  rgb = colour;
}
