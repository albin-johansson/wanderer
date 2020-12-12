#pragma once

#include <cen/rect.hpp>

#include "depth.hpp"
#include "maybe.hpp"
#include "texture_handle.hpp"

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
 * with a lower `centerY` value will be rendered before an entity with a
 * higher value.
 *
 * \headerfile depth_drawable.hpp
 */
struct depth_drawable final
{
  texture_handle texture;  ///< Handle to associated texture.
  depth_t depth{5};        ///< Render order heuristic.
  float centerY{0};  ///< The y-coordinate of the center point of the entity.
  maybe<int> layer;  ///< Optional layer index.
  cen::irect src{};  ///< Region of associated texture that will be rendered.
  cen::frect dst{};  ///< Position and size of the rendered texture, in pixels.
};

}  // namespace wanderer::comp
