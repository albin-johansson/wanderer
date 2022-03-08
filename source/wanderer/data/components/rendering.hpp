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
struct RenderBounds final
{
  usize begin_row{};  ///< The first row index (inclusive).
  usize begin_col{};  ///< The first column index (inclusive).
  usize end_row{};    ///< The terminating row index (exclusive).
  usize end_col{};    ///< The terminating column index (exclusive).
};

/**
 * \brief Represents the region of the game shown to the player.
 */
struct Viewport final
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
struct ViewportTarget final
{};

/**
 * \brief Describes a blocking animation displaying some text over an opaque background.
 */
struct CinematicFade final
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
struct Animation final
{
  usize frame{0};                  ///< Current frame index.
  usize frame_count{1};            ///< Amount of frames in the animation.
  cen::u64ms then{0};              ///< Time of the previous update of the animation.
  std::vector<cen::u64ms> delays;  ///< Duration of each frame in the animation
};

/**
 * \brief Component associated with the `animation` component for sequenced animations.
 */
struct SeqAnimation final
{
  glm::ivec2 frame_size{};
};

/**
 * \brief Component intended to accompany the `animation` component for tile animations.
 */
struct TileAnimation final
{
  std::vector<tile_id> frames;  ///< Tiles to be rendered for each frame.
};

/**
 * \brief Component by all drawable game objects.
 *
 * \details Drawable entities are first arranged according to their layers. Within each
 * layer, the render order is determined using the depth index heuristic and he
 * y-coordinates of center points. The lower the depth value, the earlier an entity is
 * rendered.
 *
 * \details The y-coordinate of an entity's center point is used when two entities feature
 * the same depth index. Similarly to the depth, an entity with a smaller center
 * y-coordinate value will be rendered before an entity with a higher value, since they
 * are "above" and therefore behind the other.
 *
 * \note Drawable entities are expected to feature `game_object` components.
 */
struct Drawable final
{
  texture_id texture{};  ///< The associated texture.
  cen::irect src;        ///< Region of associated texture that will be rendered.
  int32 layer_index{};   ///< Layer index.
  int32 depth_index{5};  ///< Render order heuristic.
};

/**
 * \brief Represents a light at a specific point in the world.
 *
 * \note Point light entities are expected to feature `game_object` components.
 */
struct PointLight final
{
  glm::vec2 offset{};     ///< Offset of the light relative to the game object position.
  float32 size{};         ///< Base size of the light.
  float32 fluctuation{};  ///< Fluctuation size in [-limit, limit].
  float32 step_size{};    ///< Size of each fluctuation increment.
  float32 limit{};        ///< Fluctuation size limit.
};

/// \} End of group components

}  // namespace wanderer::comp