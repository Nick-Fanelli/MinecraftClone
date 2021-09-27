#version 410 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexutreCoords;
layout(location = 3) in float aTextureID;

uniform mat4 uViewProjection;

out vec3 vNormal;
out vec2 vTextureCoords;
out float vTextureID;

void main() {
    vNormal = aNormal;
    vTextureCoords = aTexutreCoords;
    vTextureID = aTextureID;

    gl_Position = uViewProjection * vec4(aPosition, 1.0);
}