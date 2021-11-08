#pragma once

#include <centurion.hpp>  // iarea, farea, color
#include <entt.hpp>       // hashed_string, id_type

#include "wanderer_std.hpp"

/// \namespace wanderer::glob
/// \brief Contains various constants.
/// \ingroup core
namespace wanderer {
namespace glob {

/// \addtogroup core
/// \{

/// \name Logical size
/// \{

template <typename T = int32>
constexpr T logical_width = 960;

template <typename T = int32>
constexpr T logical_height = 540;

template <typename T = cen::iarea>
constexpr T logical_size{logical_width<typename T::value_type>,
                         logical_height<typename T::value_type>};

/// \} End of logical size

/// \name Tiles
/// \{

constexpr TileID empty_tile{0};

template <typename T = float>
constexpr T tile_width = 64;

template <typename T = float>
constexpr T tile_height = 64;

template <typename T = float2>
constexpr T tile_size{tile_width<typename T::value_type>,
                      tile_height<typename T::value_type>};

/// \} End of tiles

/// \name Humanoids
/// \{

constexpr float humanoid_draw_width{tile_width<float> * 2.0f};
constexpr float humanoid_draw_height{tile_height<float> * 2.0f};
constexpr cen::farea humanoid_draw_size{humanoid_draw_width, humanoid_draw_height};

constexpr float player_speed = 1.25f * humanoid_draw_width;
constexpr float monster_speed = 0.75f * player_speed;

/// \} End of humanoids

/// \name Day/Night-cycle
/// \{

constexpr float morning_hour = 6;

/// \} End of day/night-cycle

/// \name Events
/// \{

constexpr uint32 sleep_id = 1;
constexpr uint32 load_game_id = 2;
constexpr uint32 switch_level_id = 3;

/// \} End of events

/// \name UI
/// \{

constexpr cen::color transparent_black = cen::colors::black.with_alpha(0xBB);

constexpr int32 small_font_size = 8;
constexpr int32 medium_font_size = 16;
constexpr int32 large_font_size = 24;

constexpr entt::id_type menu_font_s = entt::hashed_string{"typewriter_s"};
constexpr entt::id_type menu_font_m = entt::hashed_string{"typewriter_m"};
constexpr entt::id_type menu_font_l = entt::hashed_string{"typewriter_l"};

constexpr float menu_row_size = 30;
constexpr float menu_col_size = 30;

constexpr float menu_rows = logical_height<float> / menu_row_size;
constexpr float menu_columns = logical_width<float> / menu_col_size;

constexpr int32 default_margin = 6;

/// \} End of UI

}  // namespace glob

[[nodiscard]] constexpr auto IsEmpty(const TileID id) noexcept -> bool
{
  return id == glob::empty_tile;
}

/// \} End of group core

}  // namespace wanderer
