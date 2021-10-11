#version 410 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in float aLightValue;
layout(location = 2) in vec2 aTexutreCoords;

uniform mat4 uViewProjection;
uniform vec3 uTransformation;

out float vLightValue;
out vec2 vTextureCoords;

void main() {

    vLightValue = aLightValue;
    vTextureCoords = aTexutreCoords;

    gl_Position = uViewProjection * vec4(aPosition + uTransformation, 1.0);
}