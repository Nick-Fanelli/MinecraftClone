#version 410 core

out vec4 outColor;

in vec3 vTextureCoords;

uniform samplerCube uSkybox;

void main() {
    outColor = texture(uSkybox, vTextureCoords);
}