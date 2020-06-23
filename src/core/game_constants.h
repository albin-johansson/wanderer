#pragma once
#include "wanderer_stdinc.h"

namespace wanderer {

template <typename T = int>
inline constexpr T g_logicalWidth{480};  // 960

template <typename T = int>
inline constexpr T g_logicalHeight{270};  // 540

template <typename T = float>
inline constexpr T g_tileSize{32};

inline constexpr float g_humanoidDrawWidth{g_tileSize<float> * 2};

inline constexpr float g_humanoidDrawHeight{g_tileSize<float> * 2};

inline constexpr float g_playerSpeed{1.25f * g_humanoidDrawWidth};

inline constexpr float g_monsterSpeed{0.75f * g_playerSpeed};

}  // namespace wanderer