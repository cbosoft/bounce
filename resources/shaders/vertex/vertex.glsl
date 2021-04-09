#version 330 core

uniform vec2 camera_position; // in world units
uniform vec2 camera_size;     // in world units
uniform float camera_angle;     // in radians
uniform vec2 centre;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colour;

out vec3 rgb;
out vec2 centre_screen_pos;

vec2 rot(float theta, vec2 pos)
{
  float c = cos(theta);
  float s = sin(theta);
  mat2 rotmat = mat2(c, -s, s, c);
  return pos*rotmat;
}

vec2 world_to_screen(vec2 p)
{
  p -= camera_position;
  p = rot(camera_angle, p);
  p /= camera_size;
  return p;
}

vec3 world_to_screen(vec3 p)
{
  return vec3(world_to_screen(p.xy), 0.0);
}

void main() {
  gl_Position = vec4(world_to_screen(pos), 1.0f);
  rgb = colour;
  centre_screen_pos = world_to_screen(centre);
}
