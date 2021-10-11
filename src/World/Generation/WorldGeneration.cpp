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

static FastNoiseLite s_CaveNoise;

static constexpr float s_Magnitude = 10.0f;
static constexpr float s_Threshold = 0.5f;

static constexpr int s_HeightDifference = 80;
static constexpr int s_DirtHeight = 5;
static constexpr int s_WaterLevel = Chunk::CHUNK_HEIGHT - 10;

// Perlin Noise World Generator
Block::Block* PerlinNoiseWorldGenerator::GetBlock(const glm::vec3& position) {

    static bool noiseInitialized = false;

    if(!noiseInitialized) {
        srand(time(nullptr));

        s_Noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        s_Noise.SetSeed(rand());
        s_Noise.SetFractalType(FastNoiseLite::FractalType_PingPong);
        s_Noise.SetFractalPingPongStrength(1.25f);

        s_CaveNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        s_CaveNoise.SetSeed(rand());
        s_CaveNoise.SetFrequency(0.03f);
        s_CaveNoise.SetFractalType(FastNoiseLite::FractalType_PingPong);
        s_CaveNoise.SetFractalPingPongStrength(1.25f);

        noiseInitialized = true;
    }

    // Bedrock
    if(position.y <= 1)
        return &Block::BEDROCK;

    int topHeight = std::min(Chunk::CHUNK_HEIGHT - ((int) (s_Noise.GetNoise(position.x, position.z) * s_Magnitude)) - s_HeightDifference, Chunk::CHUNK_HEIGHT - 1);

    // Cave
    if(position.y < topHeight - 5) {
        float caveNoise = abs(s_CaveNoise.GetNoise(position.x, position.y, position.z));

        if(caveNoise >= s_Threshold) 
            return &Block::AIR;
    }

    if(position.y == topHeight)
        return &Block::GRASS;
    else if(position.y < topHeight && position.y > topHeight - s_DirtHeight)
        return &Block::DIRT;
    else if(position.y <= topHeight - s_DirtHeight)
        return &Block::STONE;
    else {
        return &Block::AIR;
    }
}
