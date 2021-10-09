#include "WorldGeneration.h"

#include "World/Chunk.h"

Block::Block* FlatWorldGenerator::GetBlock(const glm::vec3& position) {
    if(position.y < Chunk::CHUNK_SIZE - 1)
        return &Block::DIRT;
    else
        return &Block::GRASS;
}
