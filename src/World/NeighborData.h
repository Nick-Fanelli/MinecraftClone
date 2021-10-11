#pragma once

#include "pch.h"

namespace NeighborData {

    struct NeighborData {

        glm::vec3 RelativePosition;
        glm::vec3 RelativeFacePosition[4];
        float LightValue;
        bool ShouldInvert;

        enum TextureSide {
            TextureSideTop,
            TextureSideSide,
            TextureSideBottom
        } TextureSide;

    };

    static constexpr NeighborData Data[] = {
        // Back Neighbor
        {
            { 0.0f, 0.0f, -1.0f },
            {
                { -0.5f, -0.5f, -0.5f },
                { -0.5f, +0.5f, -0.5f },
                { +0.5f, +0.5f, -0.5f },
                { +0.5f, -0.5f, -0.5f }
            },
            0.75f,
            false,
            NeighborData::TextureSideSide
        },

        // Front Neighbor
        {
            { 0.0f, 0.0f, 1.0f },
            {
                { -0.5f, -0.5f, +0.5f },
                { -0.5f, +0.5f, +0.5f },
                { +0.5f, +0.5f, +0.5f },
                { +0.5f, -0.5f, +0.5f }
            },
            0.95,
            true,
            NeighborData::TextureSideSide
        },

        // Right Neighbor
        {
            { 1.0f, 0.0f, 0.0f },
            {
                { +0.5f, -0.5f, -0.5f },
                { +0.5f, +0.5f, -0.5f },
                { +0.5f, +0.5f, +0.5f },
                { +0.5f, -0.5f, +0.5f }
            },
            0.85f,
            false,
            NeighborData::TextureSideSide
        },

        // Left Neighbor
        {
            { -1.0f, 0.0f, 0.0f },
            {
                { -0.5f, -0.5f, -0.5f },
                { -0.5f, +0.5f, -0.5f },
                { -0.5f, +0.5f, +0.5f },
                { -0.5f, -0.5f, +0.5f }
            },
            0.75f,
            true,
            NeighborData::TextureSideSide
        },

        // Top Neighbor
        {
            { 0.0f, 1.0f, 0.0f },
            {
                { -0.5f, +0.5f, +0.5f },
                { -0.5f, +0.5f, -0.5f },
                { +0.5f, +0.5f, -0.5f },
                { +0.5f, +0.5f, +0.5f }
            },
            1.0f,
            true,
            NeighborData::TextureSideTop
        },

        // Bottom Neighbor
        {
            { 0.0f, -1.0f, 0.0f },
            {
                { -0.5f, -0.5f, +0.5f },
                { -0.5f, -0.5f, -0.5f },
                { +0.5f, -0.5f, -0.5f },
                { +0.5f, -0.5f, +0.5f }
            },
            0.6f,
            false,
            NeighborData::TextureSideBottom
        }
    };
}