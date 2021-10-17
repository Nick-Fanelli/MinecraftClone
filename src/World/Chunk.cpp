#include "Chunk.h"

#include "NeighborData.h"

#include "Render/Vertex.h"
#include "World/Generation/WorldGeneration.h"

static PerlinNoiseWorldGenerator s_WorldGenerator;

static int GetBlockArrayIndex(const glm::vec3& position) {

    return (position.y * Chunk::CHUNK_AREA) + (position.z * Chunk::CHUNK_SIZE) + position.x;
}

static glm::vec3 GetBlockPosition(int index) {

    const int y = index / (Chunk::CHUNK_AREA);
    index -= (y * Chunk::CHUNK_AREA);

    const int z = index / Chunk::CHUNK_SIZE;
    const int x = index % Chunk::CHUNK_SIZE;

    return { x, y, z };
}

static bool IsBlockInBounds(const glm::vec3& position) {
    return position.x >= 0 && position.y >= 0 && position.z >= 0 && 
           position.x < Chunk::CHUNK_SIZE && position.y < Chunk::CHUNK_HEIGHT && position.z < Chunk::CHUNK_SIZE;
}

void Chunk::CreateChunk(int chunkX, int chunkZ) {
    
    m_ChunkPosition = { chunkX, 0.0f, chunkZ };

    for(uint32_t i = 0; i < m_Blocks.size(); i++) {
        auto position = GetBlockPosition(i);

        m_Blocks[i] = s_WorldGenerator.GetBlock(position + (m_ChunkPosition * (float) CHUNK_SIZE));
    }

    UpdateChunkMesh();
}

void Chunk::AddFace(std::vector<Vertex>* vertices, std::vector<uint32_t>* indices, const glm::vec3& first, const glm::vec3& second, const glm::vec3& third, const glm::vec3& fourth,
                    float lightValue, const glm::vec2& texturePosition, bool shouldInvert) {
    
    static const float sheetID = Block::GetBlockSpritesheet().GetTextureID();

    static const int sheetWidth  = Block::GetBlockSpritesheet().GetWidth()  ;
    static const int sheetHeight = Block::GetBlockSpritesheet().GetHeight() ;

    static const float textureCoordDifference = (float) Block::SpriteSheetSize / (float) sheetWidth;

    glm::vec2 textureCoords = texturePosition * textureCoordDifference;

    vertices->push_back({ first, lightValue, { textureCoords.x, textureCoords.y + textureCoordDifference } });
    vertices->push_back({ second, lightValue, textureCoords });
    vertices->push_back({ third, lightValue, { textureCoords.x + textureCoordDifference, textureCoords.y } });
    vertices->push_back({ fourth, lightValue, { textureCoords.x + textureCoordDifference, textureCoords.y + textureCoordDifference } });

    uint32_t startingValue = indices->size() > 0 ? ((indices->back()) + 1) : 0;

    if(shouldInvert) {
        indices->push_back(startingValue + 1);
        indices->push_back(startingValue);
        indices->push_back(startingValue + 2);
        indices->push_back(startingValue + 2);
        indices->push_back(startingValue);
        indices->push_back(startingValue + 3);
    } else {
        indices->push_back(startingValue);
        indices->push_back(startingValue + 1);
        indices->push_back(startingValue + 2);
        indices->push_back(startingValue);
        indices->push_back(startingValue + 2);
        indices->push_back(startingValue + 3);
    }
}

void Chunk::UpdateChunkMesh() {
    for(uint32_t i = 0; i < m_Blocks.size(); i++) {

        if(m_Blocks[i] == nullptr || m_Blocks[i] == &Block::AIR)
            continue;

        auto blockPosition = GetBlockPosition(i);

        for(auto& data : NeighborData::Data) {

            auto neighborPosition = data.RelativePosition + blockPosition;

            bool shouldDrawFace = false;

            if(!IsBlockInBounds(neighborPosition))
                // shouldDrawFace = true;
                shouldDrawFace = !s_WorldGenerator.GetBlock(neighborPosition + (m_ChunkPosition * (float) CHUNK_SIZE))->IsSolid;
            else if(!m_Blocks[GetBlockArrayIndex(neighborPosition)]->IsSolid)
                shouldDrawFace = true;

            // Draw the face
            if(shouldDrawFace) {
                glm::vec2 textureCoords;

                switch(data.TextureSide) {
                case NeighborData::NeighborData::TextureSideTop:
                    textureCoords = m_Blocks[i]->TopTexturePosition;
                    break;
                case NeighborData::NeighborData::TextureSideBottom:
                    textureCoords = m_Blocks[i]->BottomTexturePosition;
                    break;
                default: // Also TextureSideSide
                    textureCoords = m_Blocks[i]->SidesTexturePosition;
                    break;
                }

                AddFace(&m_TempVertices, &m_TempIndices,
                    data.RelativeFacePosition[0] + blockPosition,
                    data.RelativeFacePosition[1] + blockPosition,
                    data.RelativeFacePosition[2] + blockPosition,
                    data.RelativeFacePosition[3] + blockPosition,
                    data.LightValue,
                    textureCoords,
                    data.ShouldInvert
                );
            }
        }

    }

    m_ShouldCreateChunkMesh = true;
}

void Chunk::CreateMesh() {
    m_Mesh.Create(m_TempVertices, m_TempIndices);
    m_TempVertices.clear();
    m_TempIndices.clear();

    m_ShouldCreateChunkMesh = false;
}