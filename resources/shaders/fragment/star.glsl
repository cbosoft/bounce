#version 330 core
uniform float time_delta;
uniform float time;
uniform float radius;
uniform vec2 camera_position;

in vec3 rgb;
in vec2 centre_screen_pos;

out vec4 color;

void main()
{
    vec2 cpos = (centre_screen_pos + 1.0f) * vec2(1280.f, 960.f);
    vec2 ppos = gl_FragCoord.xy;
    float d_r = length(cpos - ppos)/radius/4;
    //float d = 1-clamp(dist/1000, 0, 1);
    float d = exp(-d_r)*2.0;
    //color = vec4(1.0f, 1.0f, 1.0f, 0.5f);
    color = vec4(rgb, d);
    // color = rgb*(-exp(-dist*100));
}