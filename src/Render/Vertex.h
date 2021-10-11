#pragma once

#include "pch.h"

struct Vertex {

    glm::vec3 Position;
    float LightValue;
    glm::vec2 TextureCoords;

    Vertex() = default;
    Vertex(const glm::vec3& position) : Position(position) {}
    Vertex(const glm::vec3& position, float lightValue) : Position(position), LightValue(lightValue) {}
    Vertex(const glm::vec3& position, float lightValue, const glm::vec2& textureCoords) : Position(position), LightValue(lightValue), TextureCoords(textureCoords) {}

};