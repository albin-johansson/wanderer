#pragma once

#include <centurion.hpp>  // irect, frect

#include "core/aliases/depth.hpp"
#include "core/aliases/ints.hpp"
#include "core/aliases/texture_index.hpp"

namespace wanderer::comp {

/**
 * \struct depth_drawable
 *
 * \brief Represents a drawable entity that features a depth heuristic.
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
 *
 * \headerfile depth_drawable.hpp
 */
struct depth_drawable final
{
  texture_index texture{};  ///< ID of associated texture.
  cen::irect src;           ///< Region of associated texture that will be rendered.
  cen::frect dst;           ///< Position and size of the rendered texture, in pixels.
  int layer{};              ///< Layer index.
  depth_t depth{5};         ///< Render order heuristic.
};

void serialize(auto& archive, depth_drawable& drawable, uint32 version)
{
  archive(drawable.texture, drawable.src, drawable.dst, drawable.layer, drawable.depth);
}

}  // namespace wanderer::comp
