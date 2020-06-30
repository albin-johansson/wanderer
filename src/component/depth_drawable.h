/**
 * @brief Provides the `DepthDrawable` component.
 * @file depth_drawable.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <area.h>
#include <rect.h>
#include <texture.h>

#include <entt.hpp>

#include "wanderer_stdinc.h"

namespace wanderer {  // TODO wanderer::component namespace

/**
 * @struct DepthDrawable
 * @brief Represents drawable entity that features a depth heuristic.
 *
 * @details Provides information required to be able to render entities in
 * such a way that they are arranged in relation to their depth heuristic *and*
 * the y-coordinates of their center points.
 *
 * @var DepthDrawable::texture
 * The handle to the associated image that will be rendered.
 * @var DepthDrawable::depth
 * The depth heuristic. Defaults to 5. A lower depth value indicates that the
 * entity should be rendered before another entity with a higher value.
 * @var DepthDrawable::centerY
 * The y-coordinate of the center point of the entity. This is used when two
 * entities feature the same depth value. Similarly to the depth, entities
 * with a lower `centerY` value will be rendered before an entity with a
 * higher value.
 * @var DepthDrawable::src
 * The cutout of the associated texture that will be rendered.
 * @var DepthDrawable::dst
 * The destination position and size of the rendered texture, in pixels.
 *
 * @headerfile depth_drawable.h
 */
struct DepthDrawable final {
  entt::handle<ctn::Texture> texture;  // handle to associated texture
  Depth depth{5};    // heuristic used to determine render order
  float centerY{0};  // current center point y-coordinate
  ctn::IRect src{};  // source cutout used when rendering
  ctn::FRect dst{};  // destination and size of the rendered texture
};

}  // namespace wanderer
