/**
 * @brief Provides the `Viewport` component.
 * @file viewport.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <area.h>
#include <rect.h>

#include "wanderer_stdinc.h"

namespace wanderer::component {

/**
 * @struct Viewport
 * @brief Represents an area that is visible for the player.
 *
 * @var Viewport::bounds
 * The position and size of the viewport.
 * @var Viewport::levelSize
 * The size of the level that the viewport is associated with.
 *
 * @headerfile viewport.h
 */
struct Viewport final {
  using entity = fluent::
      NamedType<entt::entity, struct ViewportEntityTag, fluent::Comparable>;
  ctn::FRect bounds{};
  ctn::FArea levelSize{};
};

}  // namespace wanderer::component
