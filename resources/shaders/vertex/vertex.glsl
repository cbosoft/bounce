#version 330 core

uniform vec2 camera_position; // in world units
uniform vec2 camera_size;     // in world units
uniform float camera_angle;   // in radians
uniform float object_angle;   // in radians
uniform vec2 centre;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 colour;
layout (location = 2) in vec2 texCoords;

out vec4 rgba;
out vec2 TexCoords;
out vec2 centre_screen_pos;
out vec2 camera_Position;

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
  vec2 p_about_c = pos.xy - centre;
  vec2 p_rotated_about_c = rot(object_angle, p_about_c);
  vec2 p_rotated = p_rotated_about_c + centre;
  gl_Position = vec4(world_to_screen(p_rotated), 0.0f, 1.0f);
  rgba = colour;
  TexCoords = texCoords;
  centre_screen_pos = world_to_screen(centre);
  camera_Position = camera_position;
}
