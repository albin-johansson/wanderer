#pragma once

#include <glm/glm.hpp>

#include "common.hpp"

namespace wanderer {

inline constexpr int32 logical_width = 960;
inline constexpr int32 logical_height = 540;
inline constexpr glm::ivec2 logical_size{logical_width, logical_height};

inline constexpr float32 logical_width_f = static_cast<float>(logical_width);
inline constexpr float32 logical_height_f = static_cast<float>(logical_height);
inline constexpr glm::fvec2 logical_size_f{logical_width_f, logical_height_f};

}  // namespace wanderer
