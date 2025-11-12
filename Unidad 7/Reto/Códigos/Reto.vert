#version 150

uniform mat4 modelViewProjectionMatrix;
in vec4 position;

uniform float mouseRange;
uniform vec2 mousePos;

void main() {
    vec4 pos = position;

    vec2 dir = pos.xy - mousePos;
    float dist = distance(pos.xy, mousePos);

    if (dist > 0.0 && dist < mouseRange) {
        float distNorm = 1.0 - (dist / mouseRange);
        dir *= distNorm;
        pos.x += dir.x;
        pos.y += dir.y;
    }

    gl_Position = modelViewProjectionMatrix * pos;
}
