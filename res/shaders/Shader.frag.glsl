#version 410 core

in float vLightValue;
in vec2 vTextureCoords;

uniform sampler2D uTexture;

out vec4 color;

void main() {

    color = vec4(vLightValue, vLightValue, vLightValue, 1.0) * texture(uTexture, vTextureCoords);
}