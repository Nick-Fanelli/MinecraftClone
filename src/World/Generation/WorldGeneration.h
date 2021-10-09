#pragma once

#include "pch.h"

#include "World/Block.h"

class WorldGenerator {

public:
    virtual Block::Block* GetBlock(const glm::vec3& position) = 0;

};

class FlatWorldGenerator : public WorldGenerator {

public:

    virtual Block::Block* GetBlock(const glm::vec3& position);

};