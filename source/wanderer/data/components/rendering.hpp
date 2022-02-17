#pragma once

#include <glm/glm.hpp>

#include "wanderer/common.hpp"

namespace wanderer::comp {

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
 * \note An entity featuring this component must also feature a `world_position`
 * component.
 */
struct viewport_target final
{
  glm::vec2 size{};  ///< The size of the target, to be able to center the viewport.
};

}  // namespace wanderer::comp