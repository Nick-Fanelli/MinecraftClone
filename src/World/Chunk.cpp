#include "Chunk.h"

#include "Render/Vertex.h"

static int GetBlockArrayIndex(int x, int y, int z) {
    return (z * Chunk::CHUNK_AREA) + (y * Chunk::CHUNK_SIZE) + x;
}

static int GetBlockArrayIndex(const glm::vec3& position) {
    return (position.z * Chunk::CHUNK_AREA) + (position.y * Chunk::CHUNK_SIZE) + position.x;
}

static glm::vec3 GetBlockPosition(int index) {
    const int z = index / (Chunk::CHUNK_AREA);
    index -= (z * Chunk::CHUNK_AREA);

    const int y = index / Chunk::CHUNK_SIZE;
    const int x = index % Chunk::CHUNK_SIZE;

    return { x, y, z };
}

static bool IsBlockInBounds(const glm::vec3& position) {
    return position.x >= 0 && position.y >= 0 && position.z >= 0 && 
           position.x < Chunk::CHUNK_SIZE && position.y < Chunk::CHUNK_SIZE && position.z < Chunk::CHUNK_SIZE;
}

void Chunk::CreateChunk() {
    for(uint32_t i = 0; i < m_Blocks.size(); i++) {
        glm::vec3 blockPosition = GetBlockPosition(i);

        if(blockPosition.y < CHUNK_SIZE - 1)
            m_Blocks[i] = &BLOCK_DIRT;
        else 
            m_Blocks[i] = &BLOCK_GRASS;
    }

    UpdateChunkMesh();
}

void Chunk::AddFace(std::vector<Vertex>* vertices, std::vector<uint32_t>* indices, const glm::vec3& first, const glm::vec3& second, const glm::vec3& third, const glm::vec3& fourth,
                    const glm::vec2& texturePosition, bool shouldInvert) {
    
    static const float sheetID = GetBlockSpritesheet().GetTextureID();

    static const int sheetWidth  = GetBlockSpritesheet().GetWidth()  ;
    static const int sheetHeight = GetBlockSpritesheet().GetHeight() ;

    static const float textureCoordDifference = (float) SpriteSheetSize / (float) sheetWidth;

    glm::vec2 textureCoords = texturePosition * textureCoordDifference;

    vertices->push_back({ first, { 0.0f, 0.0f, 1.0f }, { textureCoords.x, textureCoords.y + textureCoordDifference }, sheetID });
    vertices->push_back({ second, { 0.0f, 0.0f, 1.0f }, textureCoords, sheetID });
    vertices->push_back({ third, { 0.0f, 0.0f, 1.0f }, { textureCoords.x + textureCoordDifference, textureCoords.y }, sheetID });
    vertices->push_back({ fourth, { 0.0f, 0.0f, 1.0f }, { textureCoords.x + textureCoordDifference, textureCoords.y + textureCoordDifference }, sheetID });

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

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    for(uint32_t i = 0; i < m_Blocks.size(); i++) {

        if(m_Blocks[i] == &BLOCK_AIR)
            continue;

        auto blockPosition = GetBlockPosition(i);

        glm::vec3 backNeighbor = { blockPosition.x, blockPosition.y, blockPosition.z - 1.0f };
        glm::vec3 frontNeighbor = { blockPosition.x, blockPosition.y, blockPosition.z + 1.0f };

        glm::vec3 rightNeighbor = { blockPosition.x + 1.0f, blockPosition.y, blockPosition.z };
        glm::vec3 leftNeighbor = { blockPosition.x - 1.0f, blockPosition.y, blockPosition.z };

        glm::vec3 topNeighbor = { blockPosition.x, blockPosition.y + 1.0f, blockPosition.z };
        glm::vec3 bottomNeighbor = { blockPosition.x, blockPosition.y - 1.0f, blockPosition.z };

        // Back Face
        if(!IsBlockInBounds(backNeighbor) || !m_Blocks[GetBlockArrayIndex(backNeighbor)]->IsSolid) {
            AddFace(&vertices, &indices, 
                { blockPosition.x - 0.5f, blockPosition.y - 0.5f, blockPosition.z - 0.5f },
                { blockPosition.x - 0.5f, blockPosition.y + 0.5f, blockPosition.z - 0.5f },
                { blockPosition.x + 0.5f, blockPosition.y + 0.5f, blockPosition.z - 0.5f },
                { blockPosition.x + 0.5f, blockPosition.y - 0.5f, blockPosition.z - 0.5f },
                m_Blocks[i]->SidesTexturePosition,
                false
            );
        }

        // Front Face
        if(!IsBlockInBounds(frontNeighbor) || !m_Blocks[GetBlockArrayIndex(frontNeighbor)]->IsSolid) {
            AddFace(&vertices, &indices, 
                { blockPosition.x - 0.5f, blockPosition.y - 0.5f, blockPosition.z + 0.5f },
                { blockPosition.x - 0.5f, blockPosition.y + 0.5f, blockPosition.z + 0.5f },
                { blockPosition.x + 0.5f, blockPosition.y + 0.5f, blockPosition.z + 0.5f },
                { blockPosition.x + 0.5f, blockPosition.y - 0.5f, blockPosition.z + 0.5f },
                m_Blocks[i]->SidesTexturePosition,
                true
            );
        }

        // Right Face
        if(!IsBlockInBounds(rightNeighbor) || !m_Blocks[GetBlockArrayIndex(rightNeighbor)]->IsSolid) {
            AddFace(&vertices, &indices,
                { blockPosition.x + 0.5f, blockPosition.y - 0.5f, blockPosition.z - 0.5f },
                { blockPosition.x + 0.5f, blockPosition.y + 0.5f, blockPosition.z - 0.5f },
                { blockPosition.x + 0.5f, blockPosition.y + 0.5f, blockPosition.z + 0.5f },
                { blockPosition.x + 0.5f, blockPosition.y - 0.5f, blockPosition.z + 0.5f },
                m_Blocks[i]->SidesTexturePosition,
                false
            );
        }

        // Left Face
        if(!IsBlockInBounds(leftNeighbor) || !m_Blocks[GetBlockArrayIndex(leftNeighbor)]->IsSolid) {
            AddFace(&vertices, &indices,
                { blockPosition.x - 0.5f, blockPosition.y - 0.5f, blockPosition.z - 0.5f },
                { blockPosition.x - 0.5f, blockPosition.y + 0.5f, blockPosition.z - 0.5f },
                { blockPosition.x - 0.5f, blockPosition.y + 0.5f, blockPosition.z + 0.5f },
                { blockPosition.x - 0.5f, blockPosition.y - 0.5f, blockPosition.z + 0.5f },
                m_Blocks[i]->SidesTexturePosition,
                true
            );
        }

        // Top Face
        if(!IsBlockInBounds(topNeighbor) || !m_Blocks[GetBlockArrayIndex(topNeighbor)]->IsSolid) {
            AddFace(&vertices, &indices,
                { blockPosition.x - 0.5f, blockPosition.y + 0.5f, blockPosition.z + 0.5f },
                { blockPosition.x - 0.5f, blockPosition.y + 0.5f, blockPosition.z - 0.5f },
                { blockPosition.x + 0.5f, blockPosition.y + 0.5f, blockPosition.z - 0.5f },
                { blockPosition.x + 0.5f, blockPosition.y + 0.5f, blockPosition.z + 0.5f },
                m_Blocks[i]->TopTexturePosition,
                true
            );
        }
        
        // Bottom Face
        if(!IsBlockInBounds(bottomNeighbor) || !m_Blocks[GetBlockArrayIndex(bottomNeighbor)]->IsSolid) {
            AddFace(&vertices, &indices,
                { blockPosition.x - 0.5f, blockPosition.y - 0.5f, blockPosition.z + 0.5f },
                { blockPosition.x - 0.5f, blockPosition.y - 0.5f, blockPosition.z - 0.5f },
                { blockPosition.x + 0.5f, blockPosition.y - 0.5f, blockPosition.z - 0.5f },
                { blockPosition.x + 0.5f, blockPosition.y - 0.5f, blockPosition.z + 0.5f },
                m_Blocks[i]->BottomTexturePosition,
                false
            );
        }

    }

    m_Mesh.Create(vertices, indices);

}
