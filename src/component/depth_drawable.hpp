#pragma once

#include <area.hpp>
#include <rect.hpp>
#include <texture.hpp>

#include "wanderer_stdinc.hpp"

namespace wanderer::comp {

/**
 * @struct depth_drawable
 * @brief Represents drawable entity that features a depth heuristic.
 *
 * @details Provides information required to be able to render entities in
 * such a way that they are arranged in relation to their depth heuristic *and*
 * the y-coordinates of their center points.
 *
 * @var depth_drawable::texture
 * The handle to the associated image that will be rendered.
 * @var depth_drawable::depth
 * The depth heuristic. Defaults to 5. A lower depth value indicates that the
 * entity should be rendered before another entity with a higher value.
 * @var depth_drawable::centerY
 * The y-coordinate of the center point of the entity. This is used when two
 * entities feature the same depth value. Similarly to the depth, entities
 * with a lower `centerY` value will be rendered before an entity with a
 * higher value.
 * @var depth_drawable::src
 * The cutout of the associated texture that will be rendered.
 * @var depth_drawable::dst
 * The destination position and size of the rendered texture, in pixels.
 *
 * @headerfile depth_drawable.hpp
 */
struct depth_drawable final
{
  entt::handle<cen::texture> texture;
  depth depth{5};
  float centerY{0};
  cen::irect src{};
  cen::frect dst{};
};

}  // namespace wanderer::comp
