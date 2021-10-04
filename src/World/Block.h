#pragma once

#include "pch.h"

#include "Render/Texture.h"

static Texture s_BlockSpritesheet;
static constexpr int SpriteSheetSize = 16;

inline void InitializeBlockTextures() {
    s_BlockSpritesheet = { "res/images/texture-atlas.png" };
    s_BlockSpritesheet.Create();
}

inline void DestroyBlockTextures() {
    s_BlockSpritesheet.Destroy();
}

inline const Texture& GetBlockSpritesheet() { return s_BlockSpritesheet; }

struct Block {

    bool IsSolid;
    bool UseTexture;

    glm::vec2 TopTexturePosition;
    glm::vec2 SidesTexturePosition;
    glm::vec2 BottomTexturePosition;

};

inline Block BLOCK_AIR = { false, false };
inline Block BLOCK_GRASS = { true, true, { 0, 0 }, { 3, 0 }, { 2, 0 } };
inline Block BLOCK_DIRT = { true, true, { 2, 0 }, { 2, 0 }, { 2, 0 } };