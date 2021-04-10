#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D screenTexture;

void main()
{
    vec4 pcolor = texture(screenTexture, TexCoords);
    float brightness = length(pcolor)/1.732;
    if (brightness < 0.9) {
        color = texture(screenTexture, TexCoords);
    }
    else {
        const int n = 10;
        const float dtheta = 3.1415926*2.0/float(n);
        float theta = 0.0;
        for (int i = 0; i < n; i++) {
            vec2 d = 0.008*vec2(cos(theta), sin(theta));
            pcolor += texture(screenTexture, TexCoords+d);
            theta += dtheta;
        }
        pcolor /= float(n);
        color = pcolor;
    }
}
