#version 150

uniform vec4 globalColor;
uniform vec2 u_resolution;
uniform float time;

out vec4 outputColor;

void main() {
    // Normalizar coordenadas (0 a 1)
    vec2 uv = gl_FragCoord.xy / u_resolution;

    // Crear degradado dinámico de color según posición y tiempo
    float r = abs(sin(uv.x * 3.14 + time * 0.5));
    float g = abs(sin(uv.y * 3.14 + time * 0.7));
    float b = abs(sin((uv.x + uv.y) * 3.14 + time));

    // Combinar con color global del mouse
    vec3 finalColor = vec3(r, g, b) * globalColor.rgb;

    outputColor = vec4(finalColor, 1.0);
}
