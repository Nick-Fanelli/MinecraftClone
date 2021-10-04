#pragma once

#include "pch.h"

struct Vertex {

    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TextureCoords;

    Vertex() = default;
    Vertex(const glm::vec3& position) : Position(position) {}
    Vertex(const glm::vec3& position, const glm::vec3& normal) : Position(position), Normal(normal) {}
    Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& textureCoords) : Position(position), Normal(normal), TextureCoords(textureCoords) {}

};