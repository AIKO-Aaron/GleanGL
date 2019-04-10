uniform float numLights = 0; // Number of lights

struct lightSource {
    vec4 position; // Or direction
    vec3 color;
    float brightness;
    vec3 attenuation;
};
