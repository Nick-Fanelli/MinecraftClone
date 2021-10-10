#pragma once

#include "pch.h"

#include "World/Block.h"

class WorldGenerator {

public:
    virtual Block::Block* GetBlock(const glm::vec3& position) = 0;

};

// Flat World Generator
class FlatWorldGenerator : public WorldGenerator {

public:

    Block::Block* GetBlock(const glm::vec3& position) override;

};

// Perlin Noise World Generator
class PerlinNoiseWorldGenerator : public WorldGenerator {

public: 
    Block::Block* GetBlock(const glm::vec3& position) override;

};