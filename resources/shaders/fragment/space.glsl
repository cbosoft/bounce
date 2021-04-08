#version 330 core
uniform float time_delta;
uniform float time;
uniform vec2 camera_position;
out vec3 color;
in vec3 rgb;

#define MOD2 vec2(.16632,.17369)
#define MOD3 vec3(.16532,.17369,.15787)

float Hash( float p )
{
	vec2 p2 = fract(vec2(p) * MOD2);
    p2 += dot(p2.yx, p2.xy+19.19);
	return fract(p2.x * p2.y);
}

float Hash(vec3 p)
{
	p  = fract(p * MOD3);
  p += dot(p.xyz, p.yzx + 19.19);
  return fract(p.x * p.y * p.z);
}

float hash12(vec2 p)
{
	vec3 p3  = fract(vec3(p.xyx) * .1031);
  p3 += dot(p3, p3.yzx + 33.33);
  return fract((p3.x + p3.y) * p3.z);
}

float f(vec2 pos)
{
  return float(hash12(pos) > 0.9);
}

bool is_star(vec2 pos)
{
  float disc = 0.98;
  return Hash(pos.yxy)*Hash(pos.xyx) > disc;
}

float star_brightness(vec2 pos)
{
  const float flr = 0.1;
  float freq = Hash(pos.x) + Hash(pos.y) + 0.1;
  return (sin(time*freq) + 1.0)*(1.0 - flr)*0.5 + flr;
}

void main() {
  vec2 pos = (gl_FragCoord.xy + camera_position/10000);

    pos = -abs(pos);
  if (
      is_star(pos)
      || is_star(pos + vec2( 0, 1))
      || is_star(pos + vec2( 1, 0))
      || is_star(pos + vec2(-1, 0))
      || is_star(pos + vec2( 0,-1))
      ) {
    color = vec3(rgb*star_brightness(pos));
  }
  else {
    color = vec3(0.0);
  }
}
