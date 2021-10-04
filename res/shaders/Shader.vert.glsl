#version 410 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexutreCoords;

uniform mat4 uViewProjection;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTextureCoords;

void main() {

    vPosition = aPosition;
    vNormal = aNormal;
    vTextureCoords = aTexutreCoords;

    gl_Position = uViewProjection * vec4(aPosition, 1.0);
}