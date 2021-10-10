#include "WorldGeneration.h"

#include "World/Chunk.h"

// Flat World Generator
Block::Block* FlatWorldGenerator::GetBlock(const glm::vec3& position) {

    static constexpr int floorHeight = 4;

    if(position.y == 0)
        return &Block::BEDROCK;
    else if(position.y < floorHeight)
        return &Block::DIRT;
    else if(position.y == floorHeight)
        return &Block::GRASS;

    return &Block::AIR;
}


// Perlin Noise World Generator
Block::Block* PerlinNoiseWorldGenerator::GetBlock(const glm::vec3& position) {

}
