#pragma once
#include "types.h"

namespace wanderer {

inline constexpr int g_logicalWidth{480};  // 960

inline constexpr int g_logicalHeight{270};  // 540

template <typename T>
inline constexpr T g_tileSize{32};

inline constexpr float g_entityDrawWidth{g_tileSize<float> * 2};

inline constexpr float g_entityDrawHeight{g_tileSize<float> * 2};

inline constexpr float g_playerSpeed{1.25f * g_entityDrawWidth};

}  // namespace wanderer