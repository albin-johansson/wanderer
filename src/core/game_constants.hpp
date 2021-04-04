#pragma once

#include <centurion.hpp>

#include "float2.hpp"

namespace wanderer::glob {

template <typename T = int>
inline constexpr T logical_width{960};

template <typename T = int>
inline constexpr T logical_height{540};

template <typename T = cen::iarea>
inline constexpr T logical_size{logical_width<>, logical_height<>};

template <typename T = float>
inline constexpr T tile_width{64};

template <typename T = float>
inline constexpr T tile_height{64};

template <typename T = float2>
inline constexpr T tile_size{tile_width<typename T::value_type>,
                             tile_height<typename T::value_type>};

inline constexpr float humanoid_draw_width{tile_width<> * 2.0f};
inline constexpr float humanoid_draw_height{tile_height<> * 2.0f};

template <typename T = cen::farea>
inline constexpr T humanoid_draw_size{humanoid_draw_width, humanoid_draw_height};

inline constexpr float player_speed{1.25f * humanoid_draw_width};
inline constexpr float monster_speed{0.75f * player_speed};

inline constexpr cen::color transparent_black = cen::colors::black.with_alpha(0xAA);

}  // namespace wanderer::glob
