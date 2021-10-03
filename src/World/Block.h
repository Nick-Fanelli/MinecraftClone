#pragma once

#include "pch.h"

namespace Block {

    enum BlockType {
        AIR, GRASS
    };

    inline bool IsBlockTypeSolid(BlockType blockType) {
        switch (blockType) {
        case BlockType::AIR:
            return false;
        default:
            return true;
        }
    }
}
