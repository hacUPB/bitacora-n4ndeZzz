#version 150

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
uniform float time;

void main() {
    float displacementHeight = 100.0;
    float displacementY = sin(time + (position.x / 100.0)) * displacementHeight;

    vec4 modifiedPosition = position;
    modifiedPosition.y += displacementY;

    gl_Position = modelViewProjectionMatrix * modifiedPosition;
}
