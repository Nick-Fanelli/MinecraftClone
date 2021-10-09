#version 410 core

const float ambientStrength = 0.75;
const vec3 ambient = vec3(ambientStrength);

const vec3 lightPosition = vec3(255, 255, 255);

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTextureCoords;

uniform sampler2D uTexture;

out vec4 color;

void main() {

    vec3 lightingResult = ambient;
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(lightPosition - vPosition);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = vec3(diff);

    color = vec4(lightingResult + diffuse, 1.0) * texture(uTexture, vTextureCoords);
}