#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D screenTexture;
uniform vec4 dark_colour = vec4(35.f, 44.f, 40.f, 255.f)/255.f;
uniform vec4 light_colour = vec4(125.f, 162.f, 138.f, 255.f)/255.f;

// http://alex-charlton.com/posts/Dithering_on_the_GPU/
const int imat[64] = int[](0,  32, 8,  40, 2,  34, 10, 42,
48, 16, 56, 24, 50, 18, 58, 26,
12, 44, 4,  36, 14, 46, 6,  38,
60, 28, 52, 20, 62, 30, 54, 22,
3,  35, 11, 43, 1,  33, 9,  41,
51, 19, 59, 27, 49, 17, 57, 25,
15, 47, 7,  39, 13, 45, 5,  37,
63, 31, 55, 23, 61, 29, 53, 21);

float index_value() {
    const float sl = 8.f, sl2 = sl*sl;
    int x = int(mod(gl_FragCoord.x, sl));
    int y = int(mod(gl_FragCoord.y, sl));
    return imat[(x + 4*y)]/sl2;
}

float dither(float gray) {
    float closest_colour = (gray < 0.5) ? 0.f : 1.f;
    float distance = abs(closest_colour - gray);
    float d = index_value()+0.1;
    float second_place = 1.f - closest_colour;
    return (distance <= d) ? closest_colour : second_place;
}

void main() {
    vec4 rgb = texture(screenTexture, TexCoords);
    float gy = (rgb.x + rgb.y + rgb.z)/3.f;
    float dithered = dither(gy);
    if (dithered > 0.5f) {
        color = light_colour;
    }
    else {
        color = dark_colour;
    }
}
