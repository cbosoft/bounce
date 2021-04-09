#version 330 core

uniform vec2 camera_position; // in world units
uniform vec2 camera_size;     // in world units
uniform float camera_angle;     // in radians

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colour;

out vec3 rgb;

vec2 rot(float theta, vec2 pos)
{
  float c = cos(theta);
  float s = sin(theta);
  mat2 rotmat = mat2(c, -s, s, c);
  return pos*rotmat;
}

void main() {
  vec3 vpos = pos;
  vpos -= vec3(camera_position, 0.0f);
  vpos.xy = rot(camera_angle, vpos.xy);
  vpos.xy /= camera_size;
  gl_Position = vec4(vpos, 1.0f);
  rgb = colour;
}
