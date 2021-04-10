#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D screenTexture;

const int denominators[10] = int[](1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
const float lvls[10] = float[](1.0f, 0.5f, 1.f/3.f, 0.25f, 0.2f, 1.f/6.f, 1./7.f, 0.125f, 1./9.f, 0.1f);

void main() {
    vec4 rgb = texture(screenTexture, TexCoords);
    float gy = (rgb.x + rgb.y + rgb.z)/3.f;
    color = vec4(0.0f, 0.0f, 0.0f, 0.9f);
    int px = int(gl_FragCoord.x/1.f);
    int py = int(gl_FragCoord.y/1.f);
    for (int i = 0; i < 10; i++) {
        if (gy >= lvls[i]) {
            if (px % denominators[i] == 0 && py % denominators[i] == 0) {
                color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
            }
            break;
        }
    }
    return;
}