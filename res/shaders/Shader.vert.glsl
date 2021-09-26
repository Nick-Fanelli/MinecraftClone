#version 410 core

layout(location = 0) in vec3 aPosition;

uniform mat4 uViewProjection;

void main() {
    gl_Position = vec4(aPosition, 1.0) * uViewProjection;
}