#pragma once

#include <entt.hpp>  // hashed_string, id_type

#include "core/game_constants.hpp"

namespace wanderer::glob {

inline constexpr entt::id_type menu_font_s = entt::hashed_string{"typewriter_s"};
inline constexpr entt::id_type menu_font_m = entt::hashed_string{"typewriter_m"};
inline constexpr entt::id_type menu_font_l = entt::hashed_string{"typewriter_l"};

inline constexpr float menu_row_size = 30;
inline constexpr float menu_col_size = 30;

inline constexpr float menu_rows = logical_height<float> / menu_row_size;
inline constexpr float menu_columns = logical_width<float> / menu_col_size;

}  // namespace wanderer::glob
