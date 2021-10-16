#pragma once

#include <centurion.hpp>  // irect, frect

#include "common/ints.hpp"
#include "common/texture_index.hpp"

namespace wanderer::comp {

/**
 * \brief A component used by all drawable entities.
 *
 * \details Provides information required to be able to render entities in
 * such a way that they are arranged in relation to their depth heuristic *and*
 * the y-coordinates of their center points. The lower the depth value the
 * earlier the component is rendered.
 *
 * \details The y-coordinate of the entity's center point is used when two
 * entities feature the same depth value. Similarly to the depth, entities
 * with a lower center y-coordinate value will be rendered before an entity with
 * a higher value.
 *
 * \ingroup components
 */
struct Drawable final
{
  texture_index texture{};  ///< ID of associated texture.
  cen::irect src;           ///< Region of associated texture that will be rendered.
  cen::frect dst;           ///< Position and size of the rendered texture, in pixels.
  int32 layer{};            ///< Layer index.
  int32 depth{5};           ///< Render order heuristic.
};

}  // namespace wanderer::comp
