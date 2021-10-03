#pragma once

#include "pch.h"

inline std::ostream& operator<<(std::ostream& os, const glm::vec3& vec) {
    return os << "{ " << vec.x << ", " << vec.y << ", " << vec.z << " }";
}