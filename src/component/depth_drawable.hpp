#pragma once

#include <cen/rect.hpp>

#include "depth.hpp"
#include "ints.hpp"
#include "texture_handle.hpp"
#include "texture_id.hpp"

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
  texture_id textureId;    ///< ID of associated texture.
  int layer{};             ///< Layer index.
  depth_t depth{5};        ///< Render order heuristic.
  float centerY{0};  ///< The y-coordinate of the center point of the entity.
  cen::irect src{};  ///< Region of associated texture that will be rendered.
  cen::frect dst{};  ///< Position and size of the rendered texture, in pixels.
};

// TODO replace depth_drawable with drawable and depth_ordered components?
// struct depth_ordered final
//{
//  int layer{};       ///< Layer index.
//  depth_t depth{5};  ///< Render order heuristic.
//  float centerY{};   ///< The y-coordinate of the center point of the entity.
//};
//
// struct drawable final
//{
//  texture_handle handle;  ///< Handle to associated texture.
//  texture_id texture{};   ///< ID of associated texture.
//  cen::irect src;  ///< Region of associated texture that will be rendered.
//  cen::frect dst;  ///< Position and size of the rendered texture, in pixels.
//};

template <typename Archive>
void serialize(Archive& archive, depth_drawable& drawable, u32 version)
{
  // We don't serialize the texture
  archive(drawable.textureId,
          drawable.layer,
          drawable.depth.get(),
          drawable.centerY,
          drawable.src,
          drawable.dst);
}

}  // namespace wanderer::comp
