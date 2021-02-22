#pragma once

#include <cen/area.hpp>
#include <cen/colors.hpp>

#include "vector2.hpp"

namespace wanderer::glob {

template <typename T = int>
inline constexpr T logicalWidth{480};  // 960

template <typename T = int>
inline constexpr T logicalHeight{270};  // 540

template <typename T = cen::iarea>
inline constexpr T logicalSize{logicalWidth<>, logicalHeight<>};

template <typename T = float>
inline constexpr T tileWidth{32};

template <typename T = float>
inline constexpr T tileHeight{32};

template <typename T = vector2f>
inline constexpr T tileSize{tileWidth<typename T::value_type>,
                            tileHeight<typename T::value_type>};

inline constexpr float humanoidDrawWidth{tileWidth<> * 2.0f};

inline constexpr float humanoidDrawHeight{tileHeight<> * 2.0f};

template <typename T = cen::farea>
inline constexpr T humanoidDrawSize{humanoidDrawWidth, humanoidDrawHeight};

inline constexpr cen::farea humanoidHitboxSize{32, 32};

inline constexpr float playerSpeed{1.25f * humanoidDrawWidth};

inline constexpr float monsterSpeed{0.75f * playerSpeed};

inline constexpr cen::color transparentBlack =
    cen::colors::black.with_alpha(0xAA);

}  // namespace wanderer::glob
