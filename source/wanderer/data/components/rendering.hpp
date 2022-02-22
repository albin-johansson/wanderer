#pragma once

#include <string>  // string
#include <vector>  // vector

#include <centurion.hpp>
#include <glm/glm.hpp>

#include "wanderer/common.hpp"
#include "wanderer/core/graphics.hpp"

namespace wanderer::comp {

/// \addtogroup components
/// \{

/**
 * \brief Represents the region of a tilemap that needs to be rendered.
 */
struct render_bounds final
{
  usize begin_row{};  ///< The first row index (inclusive).
  usize begin_col{};  ///< The first column index (inclusive).
  usize end_row{};    ///< The terminating row index (exclusive).
  usize end_col{};    ///< The terminating column index (exclusive).
};

/**
 * \brief Represents the region of the game shown to the player.
 */
struct viewport final
{
  glm::vec2 offset{};     ///< The viewport offset.
  glm::vec2 size{};       ///< The viewport size.
  bool keep_in_bounds{};  ///< Flag to prevent showing areas outside of the map.
};

/**
 * \brief A tag component used by the viewport system for tracking.
 *
 * \details The viewport performs no tracking if no entity features this component.
 * Furthermore, it is expected that a maximum of one entity per registry features this
 * component.
 *
 * \note An entity featuring this component must also feature a `game_object` component.
 */
struct viewport_target final
{};

/**
 * \brief Describes a blocking animation displaying some text over an opaque background.
 */
struct cinematic_fade final
{
  cen::u64ms start{};       ///< Time of start.
  cen::u64ms transition{};  ///< Duration of the transitions.
  cen::u64ms pause{};       ///< Duration of the pause between transitions.
  cen::color bg;            ///< The background color.

  std::vector<entt::entity> labels;  ///< Associated lazy_text entities.
};

/**
 * \brief Represents a general frame-based animation.
 */
struct animation final
{
  usize frame{0};                  ///< Current frame index.
  usize frame_count{1};            ///< Amount of frames in the animation.
  cen::u64ms then{0};              ///< Time of the previous update of the animation.
  std::vector<cen::u64ms> delays;  ///< Duration of each frame in the animation
};

/**
 * \brief Component intended to accompany the `animation` component for tile animations.
 */
struct tile_animation final
{
  std::vector<tile_id> frames;  ///< Tiles to be rendered for each frame.
};

/// \} End of group components

}  // namespace wanderer::comp