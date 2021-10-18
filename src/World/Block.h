#pragma once

#include "pch.h"

#include "Render/Texture.h"

namespace Block {

    struct Block {

        bool IsSolid;
        bool UseTexture;

        glm::vec2 TopTexturePosition;
        glm::vec2 SidesTexturePosition;
        glm::vec2 BottomTexturePosition;

        Block() = default;
        Block(bool isSolid) : IsSolid(isSolid), UseTexture(false) {}
        Block(bool isSolid, const glm::vec2& texturePosition) : IsSolid(isSolid), UseTexture(true), TopTexturePosition(texturePosition),
            SidesTexturePosition(texturePosition), BottomTexturePosition(texturePosition) {}
        Block(bool isSolid, const glm::vec2& topTexturePosition, const glm::vec2& sidesTexturePosition, const glm::vec2& bottomTexturePosition) :
            IsSolid(isSolid), UseTexture(true), TopTexturePosition(topTexturePosition), SidesTexturePosition(sidesTexturePosition), BottomTexturePosition(bottomTexturePosition) {}

    };

    inline Block AIR = { false };

    inline Block GRASS = { true, { 0, 0 }, { 1, 0 }, { 2, 0 } };
    inline Block DIRT = { true, { 2, 0 } };
    inline Block STONE = { true, { 0, 1 } };
    inline Block BEDROCK = { true, { 4, 1 } };
}