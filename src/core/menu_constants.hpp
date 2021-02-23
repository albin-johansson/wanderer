#pragma once

#include <entt.hpp>

#include "game_constants.hpp"

namespace wanderer::glob {

inline constexpr entt::hashed_string menu_font_xs{"typewriter_xs"};
inline constexpr entt::hashed_string menu_font_s{"typewriter_s"};
inline constexpr entt::hashed_string menu_font_m{"typewriter_m"};
inline constexpr entt::hashed_string menu_font_l{"typewriter_l"};

inline constexpr int menu_row_size = 20;
inline constexpr int menu_col_size = 20;

inline constexpr int menu_rows = logical_height<int> / menu_row_size;
inline constexpr int menu_columns = logical_width<int> / menu_col_size;

}  // namespace wanderer::glob
