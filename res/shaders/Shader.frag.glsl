#version 410 core

in vec3 vNormal;
in vec2 vTextureCoords;
in float vTextureID;

uniform sampler2D uTexture;

out vec4 color;

void main() {
    vNormal;

    if(vTextureID == 0.0f)
        color = vec4(1.0);
    else
        color = texture(uTexture, vTextureCoords);
}