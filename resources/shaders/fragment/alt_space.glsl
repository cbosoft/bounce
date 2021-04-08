#version 330 core
uniform float time_delta;
uniform float time;
uniform vec2 camera_position;
out vec3 color;
in vec3 rgb;


// Star Nest by Pablo Roman Andrioli

// This content is under the MIT License.


#define iterations 15
#define formuparam 0.53

#define volsteps 5
#define stepsize 0.1

#define zoom   0.900
#define tile   1.00
#define speed  0.10

#define brightness 0.00315
#define darkmatter 0.200
#define distfading 0.710
#define saturation 0.9

void main()
{
	//get coords and direction
	vec2 uv = gl_FragCoord.xy/1000;
	vec3 dir = vec3(uv * zoom, 1.);
    
	vec3 from = vec3(camera_position/10000, 1.5);
    
	//volumetric rendering
	float s=0.1,fade=1.;
	vec3 v = rgb;
	for (int r = 0; r < volsteps; r++) {
		vec3 p = from + s * dir * .5;
		p = abs(vec3(tile) - mod(p, vec3(tile * 2.))); // tiling fold
		float pa, a=pa=0.;
		for (int i = 0; i < iterations; i++) { 
			p = abs(p) / dot(p, p) - formuparam; // the magic formula
			a += abs(length(p) - pa); // absolute sum of average change
			pa = length(p);
		}
		float dm = max(0., darkmatter - a * a * .001); //dark matter
		a *= a*a; // add contrast
		if (r > 6) fade *= 1. - dm; // dark matter, don't render near
		v += vec3(dm, dm*.5, 0.);
		v += fade;
		v += vec3(s,s*s,s*s*s*s)*a*brightness*fade; // coloring based on distance
		fade *= distfading; // distance fading
		s += stepsize;
	}
	v = mix(vec3(length(v)), v, saturation); //color adjust
	color = v*.005;
}
