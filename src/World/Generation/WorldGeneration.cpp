#include "WorldGeneration.h"

#include <FastNoiseLite.h>

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

static FastNoiseLite s_Noise;

static constexpr float s_Magnitude = 8.0f;
static constexpr int s_HeightDifference = 80;

// Perlin Noise World Generator
Block::Block* PerlinNoiseWorldGenerator::GetBlock(const glm::vec3& position) {

    static bool noiseInitialized = false;

    if(!noiseInitialized) {
        srand(time(nullptr));

        s_Noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        s_Noise.SetSeed(rand());
        s_Noise.SetFractalType(FastNoiseLite::FractalType_PingPong);
        s_Noise.SetFractalPingPongStrength(1.0f);

        noiseInitialized = true;
    }

    int topHeight = std::min(Chunk::CHUNK_HEIGHT - ((int) (s_Noise.GetNoise(position.x, position.z) * s_Magnitude)) - s_HeightDifference, Chunk::CHUNK_HEIGHT - 1);

    if(position.y == topHeight)
        return &Block::GRASS;
    else if(position.y < topHeight)
        return &Block::DIRT;
    else
        return &Block::AIR;
}
