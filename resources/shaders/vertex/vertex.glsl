#version 330 core

uniform vec2 camera_position; // in world units
uniform vec2 camera_size;     // in world units

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colour;

out vec3 rgb;

void main() {
  vec3 vpos = pos - vec3(camera_position, 0.0f);
  vpos.xy /= camera_size;
  gl_Position = vec4(vpos, 1.0f);
  rgb = colour;
}
