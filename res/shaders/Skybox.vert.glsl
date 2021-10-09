#version 410 core

layout(location = 0) in vec3 aPosition;

// out vec3 vTextureCoords;

uniform mat4 uViewProjection;

void main() {
    // vTextureCoords = aPosition;
    vec4 pos = uViewProjection * vec4(aPosition, 1.0);
    gl_Position = pos.xyww;
}